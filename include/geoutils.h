/*  =========================================================================
    geoutils - class description

    Copyright (c) 2017 Inkblot Software Limited.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#ifndef GEOUTILS_H_INCLUDED
#define GEOUTILS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  Include the library file with typdefs, public includes and public constants
#include "geoutils_library.h"

//  @warning THE FOLLOWING @INTERFACE BLOCK IS AUTO-GENERATED BY ZPROJECT
//  @warning Please edit the model at "api/geoutils.xml" to make changes.
//  @interface
//  This API is a draft, and may change without notice.
#ifdef GEOUTILS_BUILD_DRAFT_API
//  *** Draft method, for development use, may change without warning ***
//  Initialise GEOS with sane-default notice/error handlers.
//  Use this if you're not already initialising GEOS yourself.
//  You probably want to run at the top of main().
GEOUTILS_EXPORT void
    geoutils_initgeos (void);

//  *** Draft method, for development use, may change without warning ***
//  Close and finalise GEOS.
//  Use this if you're not already stopping GEOS yourself.
//  You probably want to run at the end of main().
GEOUTILS_EXPORT void
    geoutils_finishgeos (void);

//  *** Draft method, for development use, may change without warning ***
//  Self test of this class.
GEOUTILS_EXPORT void
    geoutils_test (bool verbose);

#endif // GEOUTILS_BUILD_DRAFT_API
//  @end

#ifdef __cplusplus
}
#endif

#endif