/*
 * triangle.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __triangle_h__
#define __triangle_h__

#include "raytracer/util/logging.h"
#include "raytracer/config/config.h"
#include "raytracer/domain/vector_3D.h"
#include "raytracer/domain/shapes/shape.h"
#include "raytracer/domain/ray.h"
#include "Eigen/Dense"

#include <vector>

class Triangle : public Shape { 

	public:
		Triangle( const RGB& k_diff, const RGB& k_ambient, double k_specular, double n_specular, const Vector_3D& a, const Vector_3D& b, const Vector_3D& c );
		~Triangle() { }

		bool is_intersected( Ray r );

		// TODO these rays should be passed by reference
		boost::optional<double> intersected_at( Ray r ) ;

		Vector_3D normal_at(const Ray& view_ray, double t_of_intersect);

#ifdef LOGGING
		std::string stringify_object() const;
#endif

	protected:
		std::vector<Vector_3D> vertices;

	private:
		Eigen::Matrix<double, 4, 4> A_cache, A_cache_I;
		Eigen::Matrix<double, 4, 1> B_cache, solution;
		Vector_3D normal_vector;
		void push_vectors_into_matrix();
		void push_constants_into_matrix();

};

#endif /* !__triangle_h__ */

