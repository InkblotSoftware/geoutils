/*  =========================================================================
    geoutils - class description

    Copyright (c) 2017 Inkblot Software Limited.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

/*
@header
    geoutils -
@discuss
@end
*/

#include "geoutils_classes.h"

#include <stdarg.h>

#include <geos_c.h>

//  --------------------------------------------------------------------------
//  GEOS event handlers

static void
default_geos_notice_handler (const char *fmt, ...)
{
    va_list ap;
    fprintf (stderr, "GEOS NOTICE: ");
    
    va_start (ap, fmt);
    vfprintf (stderr, fmt, ap);
    va_end   (ap);
    
    fprintf  (stderr, "\n");
    fflush (stderr);
}

static void
default_geos_error_handler (const char *fmt, ...)
{
    va_list ap;
    fprintf (stderr, "GEOS ERROR: ");
    
    va_start (ap, fmt);
    vfprintf (stderr, fmt, ap);
    va_end   (ap);
    
    fprintf  (stderr, "\n");
    fflush (stderr);
}


//  --------------------------------------------------------------------------
//  Initialising/finishing GEOS

void
geoutils_initgeos ()
{
    initGEOS (default_geos_notice_handler,
              default_geos_error_handler);
}

void
geoutils_finishgeos ()
{
    finishGEOS();
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
geoutils_test (bool verbose)
{
    printf (" * geoutils: ");

    //  @selftest

    // We can't do much more than start and stop, and see if anything crashes
    geoutils_initgeos ();
    geoutils_finishgeos ();

    //  @end
    printf ("OK\n");
}



/* //  Structure of our class */

/* struct _geoutils_t { */
/*     int filler;     //  Declare class properties here */
/* }; */


/* //  -------------------------------------------------------------------------- */
/* //  Create a new geoutils */

/* geoutils_t * */
/* geoutils_new (void) */
/* { */
/*     geoutils_t *self = (geoutils_t *) zmalloc (sizeof (geoutils_t)); */
/*     assert (self); */
/*     //  Initialize class properties here */
/*     return self; */
/* } */


/* //  -------------------------------------------------------------------------- */
/* //  Destroy the geoutils */

/* void */
/* geoutils_destroy (geoutils_t **self_p) */
/* { */
/*     assert (self_p); */
/*     if (*self_p) { */
/*         geoutils_t *self = *self_p; */
/*         //  Free class properties here */
/*         //  Free object itself */
/*         free (self); */
/*         *self_p = NULL; */
/*     } */
/* } */
