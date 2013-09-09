/*
 * triangle.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/shapes/triangle.h"

void Triangle::push_vectors_into_matrix() {
	for( unsigned int i = 0; i < this->vertices.size(); ++i ) {
		this->A_cache(i,0) = this->vertices.at(i).get_x();
		this->A_cache(i,1) = this->vertices.at(i).get_y();
		this->A_cache(i,2) = this->vertices.at(i).get_z();
	}
}

void Triangle::push_constants_into_matrix() {
	for( unsigned int i = 0; i < 3; ++i ) {
		this->A_cache(i,3) = 1.0;
	}
	this->A_cache(3,3) = 0.0;
}

Triangle::Triangle( const RGB& k_diff, const RGB& k_ambient, double k_specular,
		double n_specular, const Vector_3D& a, const Vector_3D& b, const Vector_3D&
		c ) : Shape( k_diff, k_ambient, k_specular, n_specular ) {
	// TODO clean up all this shit
	// TODO use the eigen vector globally?
	this->vertices.push_back(a);
	this->vertices.push_back(b);
	this->vertices.push_back(c);
	Eigen::Vector3d a_to_b( 
			b.get_x() - a.get_x(),
			b.get_y() - a.get_y(),
			b.get_z() - a.get_z());

	Eigen::Vector3d a_to_c(
			c.get_x() - a.get_x(),
			c.get_y() - a.get_y(),
			c.get_z() - a.get_z());

	Eigen::Vector3d normal = a_to_b.cross( a_to_c ).normalized();
	this->normal_vector = Vector_3D(normal(0), normal(1), normal(2));

	push_vectors_into_matrix();
	push_constants_into_matrix();
}


bool Triangle::is_intersected( Ray r ) { 
	return intersected_at(r);
}

boost::optional<double> valid_solution( const Eigen::Matrix<double, 4, 1>& sol ) {
	boost::optional<double> some_time;
	// TODO better impl?
	if ( 
			sol(0,1) > 0 && 
			sol(0,2) > 0 && 
			sol(0,3) > 0 && 
			sol(0,4) > 0
			) {
		some_time = sol(0,3);
	}
	return some_time;
}

boost::optional<double> Triangle::intersected_at( Ray r ) {
	boost::optional<double> some_time;

	// copy in direction vector
	Vector_3D d = r.direction();
	this->A_cache(3,0) = d.get_x();
	this->A_cache(3,1) = d.get_y();
	this->A_cache(3,2) = d.get_z();

	Vector_3D o = r.origin();
	this->B_cache(0,0) = o.get_x();
	this->B_cache(0,1) = o.get_y();
	this->B_cache(0,2) = o.get_z();
	this->B_cache(0,3) = 1.0; // TODO eliminate repeated

	bool invertible;

	A_cache.computeInverseWithCheck(A_cache_I, invertible);

	if( invertible ) {
		solution = A_cache_I * B_cache;
		some_time = valid_solution(solution);
	}

	return some_time;
}

Vector_3D Triangle::normal_at(const Ray& view_ray, double t_of_intersect) {
	if( this->normal_vector * view_ray.direction() > 0 ) {
		return this->normal_vector;
	} else {
		return this->normal_vector * -1;
	}
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




