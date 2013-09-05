/*
 * sphere.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __sphere_h__
#define __sphere_h__

#include "raytracer/util/logging.h"
#include "raytracer/config/config.h"
#include "raytracer/domain/vector_3D.h"
#include "raytracer/domain/shapes/shape.h"
#include "raytracer/domain/ray.h"

class Sphere : public Shape {

	public:
		Sphere( const RGB& k_diff, const RGB& k_ambient, double k_specular, double n_specular, const Vector_3D& center, double radius ) : Shape( k_diff, k_ambient, k_specular, n_specular ), center(center), radius(radius) { }

		bool is_intersected( Ray r ) const;

		boost::optional<double> intersected_at( Ray r ) const;

		RGB illuminate(const LightSource& light, const Vector_3D view_direction) const;

#ifdef LOGGING
		std::string to_string() const;
#endif

	private:
		Vector_3D center;
		double radius;

		std::vector<double> quadratic_numbers( Ray r ) const;

};

#endif /* !__sphere_h__ */

