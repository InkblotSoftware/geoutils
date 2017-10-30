/*  =========================================================================
    geoutils - generated layer of public API

    Copyright (c) 2017 Inkblot Software Limited.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
    =========================================================================
*/

#ifndef GEOUTILS_LIBRARY_H_INCLUDED
#define GEOUTILS_LIBRARY_H_INCLUDED

//  Set up environment for the application

//  External dependencies
#include <czmq.h>
#include <geos_c.h>

//  GEOUTILS version macros for compile-time API detection
#define GEOUTILS_VERSION_MAJOR 0
#define GEOUTILS_VERSION_MINOR 0
#define GEOUTILS_VERSION_PATCH 0

#define GEOUTILS_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define GEOUTILS_VERSION \
    GEOUTILS_MAKE_VERSION(GEOUTILS_VERSION_MAJOR, GEOUTILS_VERSION_MINOR, GEOUTILS_VERSION_PATCH)

#if defined (__WINDOWS__)
#   if defined GEOUTILS_STATIC
#       define GEOUTILS_EXPORT
#   elif defined GEOUTILS_INTERNAL_BUILD
#       if defined DLL_EXPORT
#           define GEOUTILS_EXPORT __declspec(dllexport)
#       else
#           define GEOUTILS_EXPORT
#       endif
#   elif defined GEOUTILS_EXPORTS
#       define GEOUTILS_EXPORT __declspec(dllexport)
#   else
#       define GEOUTILS_EXPORT __declspec(dllimport)
#   endif
#   define GEOUTILS_PRIVATE
#else
#   define GEOUTILS_EXPORT
#   if (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
#       define GEOUTILS_PRIVATE __attribute__ ((visibility ("hidden")))
#   else
#       define GEOUTILS_PRIVATE
#   endif
#endif

//  Project has no stable classes, so we build the draft API
#undef  GEOUTILS_BUILD_DRAFT_API
#define GEOUTILS_BUILD_DRAFT_API

//  Opaque class structures to allow forward references
//  These classes are stable or legacy and built in all releases
//  Draft classes are by default not built in stable releases
#ifdef GEOUTILS_BUILD_DRAFT_API
typedef struct _geopip_t geopip_t;
#define GEOPIP_T_DEFINED
typedef struct _geoutils_t geoutils_t;
#define GEOUTILS_T_DEFINED
typedef struct _geodist_t geodist_t;
#define GEODIST_T_DEFINED
#endif // GEOUTILS_BUILD_DRAFT_API


//  Public classes, each with its own header file
#include "geoutils_gugeopos.h"
#ifdef GEOUTILS_BUILD_DRAFT_API
#include "geopip.h"
#include "geodist.h"
#endif // GEOUTILS_BUILD_DRAFT_API

#ifdef GEOUTILS_BUILD_DRAFT_API
//  Self test for private classes
GEOUTILS_EXPORT void
    geoutils_private_selftest (bool verbose);
#endif // GEOUTILS_BUILD_DRAFT_API

#endif
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
