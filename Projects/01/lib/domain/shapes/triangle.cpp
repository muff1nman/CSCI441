/*
 * triangle.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/shapes/triangle.h"
#include "Eigen/Dense"

Triangle::Triangle( const RGB& k_diff, const RGB& k_ambient, double k_specular,
		double n_specular, const Vector_3D& a, const Vector_3D& b, const Vector_3D&
		c ) : Shape( k_diff, k_ambient, k_specular, n_specular ) {
	this->vertices.push_back(a);
	this->vertices.push_back(b);
	this->vertices.push_back(c);
}


bool Triangle::is_intersected( Ray r ) const { 
	// TODO
	return false;
}

boost::optional<double> Triangle::intersected_at( Ray r ) const {
	// TODO
	boost::optional<double> some_time;
	return some_time;
}

Vector_3D Triangle::normal_at(const Ray& view_ray, double t_of_intersect) const {
	// TODO
	return Vector_3D();
}

#ifdef LOGGING
std::string Triangle::stringify_object() const {
	std::string info = Material::stringify_object() + list_sep;
	for( unsigned int i = 0; i < this->vertices.size(); ++i ) {
		info += (char) ((int)'a' + i ) + this->vertices.at(i).to_string() + list_sep;
	}
	return info;
}
#endif




