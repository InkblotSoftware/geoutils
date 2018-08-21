/*  =========================================================================
    geodist - class description

    Copyright (c) 2017 Inkblot Software Limited.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

/*
@header
    geodist -
@discuss
@end
*/

#include "geoutils_classes.h"

#include <math.h>


//  --------------------------------------------------------------------------
//  Util funcs

static double
s_degToRad (double degs)
{
    return degs * (M_PI / 180.0);
}


//  --------------------------------------------------------------------------
//  Haversine formula dist calc

static const double s_earthRadius_metres = 6367444.7;

// Pass in radians
static double
s_arclength_haver (double lat1, double lon1,
                   double lat2, double lon2)
{
    double latArc = lat1 - lat2;
    double lonArc = lon1 - lon2;

    double latH = sin (latArc * 0.5);
    latH *= latH;

    double lonH = sin (lonArc * 0.5);
    lonH *= lonH;

    double tmp = cos (lat1) * cos (lat2);
    return 2.0 * asin (sqrt (latH + tmp * lonH));
}

double
geodist_haver (GUGeoPos pos1, GUGeoPos pos2)
{
    return   s_earthRadius_metres
           * s_arclength_haver (s_degToRad (pos1.lat), s_degToRad (pos1.lon),
                                s_degToRad (pos2.lat), s_degToRad (pos2.lon));
}


//  --------------------------------------------------------------------------
//  Self test of this class

// If your selftest reads SCMed fixture data, please keep it in
// src/selftest-ro; if your test creates filesystem objects, please
// do so under src/selftest-rw.
// The following pattern is suggested for C selftest code:
//    char *filename = NULL;
//    filename = zsys_sprintf ("%s/%s", SELFTEST_DIR_RO, "mytemplate.file");
//    assert (filename);
//    ... use the "filename" for I/O ...
//    zstr_free (&filename);
// This way the same "filename" variable can be reused for many subtests.
#define SELFTEST_DIR_RO "src/selftest-ro"
#define SELFTEST_DIR_RW "src/selftest-rw"

void
geodist_test (bool verbose)
{
    printf (" * geodist: ");

    //  @selftest

    // -- Zero
    {
        GUGeoPos somepos = { .lat = 10.0, .lon = 20.0 };
        assert (geodist_haver (somepos, somepos) == 0);
    }

    // -- Longish distance
    {
        GUGeoPos londonPos = { .lat=51.5072, .lon=0.1275 };
        GUGeoPos parisPos  = { .lat=48.8567, .lon=2.3508 };

        double distMetres_londonParis = 334824.019;  // ish
        double calcDist = geodist_haver (londonPos, parisPos);

        assert (calcDist * 0.98        <= distMetres_londonParis);
        assert (distMetres_londonParis <= calcDist * 1.02);
    }

    // -- Short dist, should be accurate
    {
        double targDist = 155.74;
        double calcDist = geodist_haver ((GUGeoPos){.lat=10.0, .lon=20.0},
                                         (GUGeoPos){.lat=10.001, .lon=20.001});

        assert (calcDist * 0.992 <= targDist);
        assert (targDist         <= calcDist * 1.002);
    }

    //  @end
    printf ("OK\n");
}

