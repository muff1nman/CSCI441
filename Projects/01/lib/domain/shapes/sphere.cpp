/*
 * sphere.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/shapes/sphere.h"
#include "raytracer/util/quad.h"
#include "raytracer/util/negative.h"

std::vector<double> Sphere::quadratic_numbers( Ray r ) const {
	std::vector<double> a_b_c(3);
	a_b_c.push_back(r.direction() * r.direction());
	a_b_c.push_back(2.0 * (r.origin() - this->center) * r.direction());
	a_b_c.push_back((r.origin() - this->center) * (r.origin() - this->center) - this->radius * this->radius);
	return a_b_c;
}

bool Sphere::is_intersected( Ray r ) const {
	return intersected_at( r );
}


RGB Sphere::illuminate(const LightSource& light, const Vector_3D view_direction) const {
	return this->k_diff;
}

boost::optional<double> Sphere::intersected_at( Ray r ) const {
	boost::optional<double> t;
	std::vector<double> q_inputs = quadratic_numbers( r );
	double dis = discriminate( q_inputs[0], q_inputs[1], q_inputs[2] );
	if (dis < 0 ) {
		return t;
	} else {
		std::vector<double> roots = quadratic_roots( q_inputs[0], q_inputs[1], q_inputs[2] );
		t = first_nonnegative<double>(roots);
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


