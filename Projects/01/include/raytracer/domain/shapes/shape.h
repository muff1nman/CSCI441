/*
 * shape.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __shape_h__
#define __shape_h__

#include "raytracer/intersection/intersectee.h"

class Shape : public Intersectee {
	virtual bool is_intersected( Ray r ) const = 0;

	virtual double intersected_at( Ray r ) const = 0;
};

#endif /* !__shape_h__ */

