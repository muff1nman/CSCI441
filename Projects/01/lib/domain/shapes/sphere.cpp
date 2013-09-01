/*
 * sphere.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/shapes/sphere.h"


bool Sphere::is_intersected( Ray r ) const {
	// TODO
	return true;
}

double Sphere::intersected_at( Ray r ) const {
	// TODO
	return 1.0;
}

#ifdef LOGGING
std::string Sphere::to_string() const {
	std::string info = "";
	info += nested_start;
	{
		info += "radius: " + boost::lexical_cast<std::string>(radius) + list_sep;
		info += "center: " + this->center.to_string() + sep;
	}
	info += nested_finish;
	return info;
}
#endif


