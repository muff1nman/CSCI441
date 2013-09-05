/*
 * ray.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/ray.h"


Vector_3D Ray::at(double some_time) const {
	return this->direction() * some_time + this->start;
}


