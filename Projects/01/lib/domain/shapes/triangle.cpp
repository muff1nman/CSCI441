/*
 * triangle.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/shapes/triangle.h"

void Triangle::push_vectors_into_matrix() {
	for( unsigned int i = 0; i < this->vertices.size(); ++i ) {
		(*A_cache)(0,i) = this->vertices.at(i).get_x();
		(*A_cache)(1,i) = this->vertices.at(i).get_y();
		(*A_cache)(2,i) = this->vertices.at(i).get_z();
	}
}

void Triangle::push_constants_into_matrix() {
	for( unsigned int i = 0; i < 3; ++i ) {
		(*A_cache)(3,i) = 1.0;
	}
	(*A_cache)(3,3) = 0.0;
}

Triangle::Triangle( const SimpleEnvironment* parent, const RGB& k_diff, const RGB& k_ambient, double k_specular,
		double n_specular, const Vector_3D& a, const Vector_3D& b, const Vector_3D&
		c ) : Shape( parent, k_diff, k_ambient, k_specular, n_specular ) {
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

	this->A_cache = new Eigen::Matrix<double, 4, 4>();
	this->A_cache_I = new Eigen::Matrix<double, 4, 4>(); 
	this->B_cache = new Eigen::Matrix<double, 4, 1>();
	this->solution = new Eigen::Matrix<double, 4, 1>();

	push_vectors_into_matrix();
	push_constants_into_matrix();

}

Triangle::~Triangle() {
	delete A_cache;
	delete A_cache_I;
	delete B_cache;
	delete solution;
}


bool Triangle::is_intersected( Ray r ) const { 
	return intersected_at(r);
}

boost::optional<double> valid_solution( const Eigen::Matrix<double, 4, 1>& sol ) {
	boost::optional<double> some_time;
	// TODO better impl?
	if ( 
			sol(0,0) > 0 && 
			sol(1,0) > 0 && 
			sol(2,0) > 0 && 
			sol(3,0) > 0
			) {

		some_time = sol(3,0);
	}
	return some_time;
}

boost::optional<double> Triangle::intersected_at( Ray r ) const {
	boost::optional<double> some_time;

	// copy in direction vector
	Vector_3D d = r.direction();
	(*A_cache)(0,3) = -d.get_x();
	(*A_cache)(1,3) = -d.get_y();
	(*A_cache)(2,3) = -d.get_z();


	Vector_3D o = r.origin();

	(*B_cache)(0,0) = o.get_x();
	(*B_cache)(1,0) = o.get_y();
	(*B_cache)(2,0) = o.get_z();
	(*B_cache)(3,0) = 1.0; // TODO eliminate repeated

	bool invertible;

	A_cache->computeInverseWithCheck(*A_cache_I, invertible);

	if( invertible ) {
		*solution = *A_cache_I * *B_cache;
		some_time = valid_solution(*solution);
	}

	return some_time;
}

Vector_3D Triangle::normal_at(const Ray& view_ray, double t_of_intersect) const {
	// The negative one is so that we can get the ray switched
	if( this->normal_vector * ( -1 * view_ray.direction() ) >= 0 ) {
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




