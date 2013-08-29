/*
 * util.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __util_h__
#define __util_h__

#include "raytracer/domain/ray.h"
#include "raytracer/domain/shape.h"
#include <vector>

/**
 * Returns the ID of the closest shape that is intersected by the given ray
 *
 * Throws an exception if 
 */
int closest_intersection( const Ray& ray, const std::vector<Shape>& shape_list) {
	// TODO
	return 0;
}

#endif /* !__util_h__ */

