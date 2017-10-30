geoutils
========
Geospatial utilities C library

For when you just want to add a bit of geospatial to your program.
GEOS does some of the heavy lifting.

Assume WGS84 for everything, and positions in degrees across the API.


Classes
-------

- __geodist__ - Functions for calculating distance between points
- __geopip__ - Checks whether geo positions are within a WKT provided polygon

In order to avoid order-of-argument errors, positions are represented by
the GUGeoPos struct. It's particularly useful with compound literals:

```C
GUGeoPos somePos = {.lat = 10.0, .lon = 20.0};
some_fun ((GUGeoPos){.lat=10.0, .lon=20.0});
```

Like the rest of the API, GUGeoPos objects should only store degrees.

Note that GEOS-using classes like geopip initialise GEOS during their ctrs
using geoutils_initgeos(), so if you've already done so your
notice/error handlers will be overwritten with the 'sane defaults' provided
by this library.


Example
-------

```C
// -- geodist

GUGeoPos pos1 = {.lat = 10.0, .lon=20.0};
GUGeoPos pos1 = {.lat = 11.0, .lon=21.0};

printf ("Distance between positions: %d\n", geodist_haver (pos1, pos2));

// -- geopip

GUGeoPos londonPos = { .lat=51.5072, .lon=0.1275 };
GUGeoPos parisPos  = { .lat=48.8567, .lon=2.3508 };

char *wkt = zsys_sprintf ("POLYGON (( %f %f, %f %f,"
                                     "%f %f, %f %f,"
                                     "%f %f ))",
                          londonPos.lon-1, londonPos.lat+1,
                          londonPos.lon+1, londonPos.lat+1,
                          londonPos.lon+1, londonPos.lat-1,
                          londonPos.lon-1, londonPos.lat-1,
                          londonPos.lon-1, londonPos.lat+1);
assert (wkt);
    
geopip_t *pip = geopip_new_wkt (wkt);
assert (pip);
zstr_free (&wkt);

assert (geopip_contains (pip, londonPos));
assert (! geopip_contains (pip, parisPos));

geopip_destroy (&pip);

// Finish GEOS, probably put this at the end of main()
geoutils_finishgeos ();
```


Full API
--------

**geodist**

```C
//  Returns the distance between two points in metres.
//  Calcualted using the haversine formula, so not accurate over
//  large distances.
GEOUTILS_EXPORT double
    geodist_haver (GUGeoPos pos1, GUGeoPos pos2);
    
//  Self test of this class.
GEOUTILS_EXPORT void
    geodist_test (bool verbose);
```

**geopip**
```C
//  Construct from a Well Known Text text string
GEOUTILS_EXPORT geopip_t *
    geopip_new_wkt (const char *wkt_str);

//  Destroy the geopip.
GEOUTILS_EXPORT void
    geopip_destroy (geopip_t **self_p);

//  Does the polygon contain the provided point?
GEOUTILS_EXPORT bool
    geopip_contains (geopip_t *self, GUGeoPos geopos);

//  Self test of this class.
GEOUTILS_EXPORT void
    geopip_test (bool verbose);
```
