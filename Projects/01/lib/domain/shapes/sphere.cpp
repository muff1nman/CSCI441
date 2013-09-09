/*
 * sphere.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/shapes/sphere.h"
#include "raytracer/util/quad.h"
#include "raytracer/util/negative.h"

void Sphere::quadratic_numbers( Ray r ) const {
	this->quadratic_roots_save->clear();
	quadratic_roots_save->push_back(r.direction() * r.direction());
	quadratic_roots_save->push_back(2.0 * (r.origin() - this->center) * r.direction());
	Vector_3D to_b_squared = r.origin() - this->center;
	quadratic_roots_save->push_back((to_b_squared * to_b_squared) - this->radius * this->radius);
}

bool Sphere::is_intersected( Ray r ) const {
	return intersected_at( r );
}

boost::optional<double> Sphere::intersected_at( Ray r ) const {
	boost::optional<double> t;
	quadratic_numbers( r );
	double dis = discriminate( quadratic_roots_save->at(0), quadratic_roots_save->at(1), quadratic_roots_save->at(2) );
	if (dis < 0 ) {
		return t;
	} else {
		quadratic_roots( quadratic_roots_save->at(0), quadratic_roots_save->at(1), quadratic_roots_save->at(2), *quadratic_roots_save );
		t = first_nonnegative<double>(*quadratic_roots_save);
		return t;
	}
}

#ifdef LOGGING
std::string Sphere::stringify_object() const {
	std::string info = Material::stringify_object() + list_sep;
	info += "radius: " + boost::lexical_cast<std::string>(radius) + list_sep;
	info += "center: " + this->center.to_string() + sep;
	return info;
}
#endif


