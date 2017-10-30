/*  =========================================================================
    geopip - class description

    Copyright (c) 2017 Inkblot Software Limited.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

/*
@header
    geopip -
@discuss
@end
*/

#include "geoutils_classes.h"

//  Structure of our class

struct _geopip_t {
    // The poly we're testing in; set for good in ctr
    GEOSGeometry *geos_geom;
    const GEOSPreparedGeometry *geos_prepgeom;
};


//  --------------------------------------------------------------------------
//  Create a new geopip

geopip_t *
geopip_new_wkt (const char *wkt_str)
{
    assert (wkt_str);
    geopip_t *self = (geopip_t *) zmalloc (sizeof (geopip_t));
    assert (self);
    //  Initialize class properties here

    GEOSWKTReader *reader = GEOSWKTReader_create();
    assert (reader);

    self->geos_geom = GEOSWKTReader_read (reader, wkt_str);
    if (! self->geos_geom)
        goto die;

    self->geos_prepgeom = GEOSPrepare (self->geos_geom);
    if (! self->geos_prepgeom)
        goto die;

    GEOSWKTReader_destroy (reader);
    return self;

 die:
    GEOSWKTReader_destroy (reader);
    geopip_destroy (&self);
    return NULL;
}


//  --------------------------------------------------------------------------
//  Destroy the geopip

void
geopip_destroy (geopip_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        geopip_t *self = *self_p;
        //  Free class properties here
        if (self->geos_prepgeom)
            GEOSPreparedGeom_destroy (self->geos_prepgeom);
        if (self->geos_geom)
            GEOSGeom_destroy (self->geos_geom);
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Does the geom contain a given point?

bool
geopip_contains (geopip_t *self, GUGeoPos pos)
{
    GEOSCoordSequence *coordSeq = GEOSCoordSeq_create (1, 1); // size,dims
    assert (coordSeq);
    GEOSCoordSeq_setX (coordSeq, 0, pos.lon);
    GEOSCoordSeq_setY (coordSeq, 0, pos.lat);

    // Takes ownership of coordSeq
    GEOSGeometry *point = GEOSGeom_createPoint (coordSeq);
    assert (point);

    bool res = GEOSPreparedContains (self->geos_prepgeom, point);
    GEOSGeom_destroy (point);
    return res;
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
geopip_test (bool verbose)
{
    printf (" * geopip: ");

    // Start by setting up geos (we assume all self tests finish geos after done)
    geoutils_initgeos ();

    // -- First check it fails on broken wkt
    
    geopip_t *badself = geopip_new_wkt ("ASDFASDF");
    assert (! badself);

    // -- Now test a real polygon contains the right poses

    // Two specific points
    GUGeoPos londonPos = { .lat=51.5072, .lon=0.1275 };
    GUGeoPos parisPos  = { .lat=48.8567, .lon=2.3508 };

    // Box around London
    char *wkt = zsys_sprintf ("POLYGON (( %f %f, %f %f,"
                                         "%f %f, %f %f,"
                                         "%f %f ))",
                              londonPos.lon-1, londonPos.lat+1,
                              londonPos.lon+1, londonPos.lat+1,
                              londonPos.lon+1, londonPos.lat-1,
                              londonPos.lon-1, londonPos.lat-1,
                              londonPos.lon-1, londonPos.lat+1);
    assert (wkt);
    
    geopip_t *self = geopip_new_wkt (wkt);
    assert (self);
    zstr_free (&wkt);

    assert (geopip_contains (self, londonPos));
    assert (! geopip_contains (self, parisPos));

    geopip_destroy (&self);

    // Be polite and finish geos
    geoutils_finishgeos ();

    printf ("OK\n");
}
