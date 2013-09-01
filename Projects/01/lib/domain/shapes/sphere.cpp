/*
 * sphere.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/shapes/sphere.h"
#include "raytracer/util/quad.h"


bool Sphere::is_intersected( Ray r ) const {
	// TODO
	return true;
}

boost::optional<double> Sphere::intersected_at( Ray r ) const {
	boost::optional<double> t;
	if (!this->is_intersected(r)) {
		return t;
	} else {
		double A = r.direction() * r.direction();
		double B = 2.0 * (r.origin() - this->center) * r.direction();
		double C = (r.origin() - this->center) * (r.origin() - this->center) - this->radius * this->radius;
		std::vector<double> roots = quadratic_roots( A, B, C );
		t = roots[0];
		return t;
	}
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


