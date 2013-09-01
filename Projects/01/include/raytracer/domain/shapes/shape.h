/*
 * shape.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __shape_h__
#define __shape_h__

#include "raytracer/intersection/intersectee.h"
#include "raytracer/util/logging.h"

class Shape : public Intersectee, public Logging {
};

#endif /* !__shape_h__ */

