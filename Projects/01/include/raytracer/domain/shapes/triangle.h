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

#include <vector>

class Triangle : public Shape { 

	public:
		Triangle( const RGB& k_diff, const RGB& k_ambient, double k_specular, double n_specular, const Vector_3D& a, const Vector_3D& b, const Vector_3D& c );
		~Triangle() { }

		bool is_intersected( Ray r ) const;

		boost::optional<double> intersected_at( Ray r ) const;

		Vector_3D normal_at(const Ray& view_ray, double t_of_intersect) const;

#ifdef LOGGING
		std::string stringify_object() const;
#endif

	protected:
		std::vector<Vector_3D> vertices;


};

#endif /* !__triangle_h__ */

