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

#include <vector>

class Sphere : public Shape {

	public:
		Sphere( const RGB& k_diff, const RGB& k_ambient, double k_specular, double n_specular, const Vector_3D& center, double radius ) : Shape( k_diff, k_ambient, k_specular, n_specular ), center(center), radius(radius) { 
			this->quadratic_roots_save = new std::vector<double>(3);
			this->quadractic_numbers_save = new std::vector<double>(3);
		}

		~Sphere() {
			delete this->quadratic_roots_save;
			delete this->quadractic_numbers_save;
		}

		bool is_intersected( Ray r ) const;

		boost::optional<double> intersected_at( Ray r ) const;

		Vector_3D normal_at(const Ray& view_ray, double t_of_intersect) const {
			return (view_ray.at(t_of_intersect) - this->center).normal();
		}

#ifdef LOGGING
		std::string stringify_object() const;
#endif

	protected:
		Vector_3D center;
		double radius;

		void quadratic_numbers( Ray r ) const;

	private:
		std::vector<double>* quadratic_roots_save;
		std::vector<double>* quadractic_numbers_save;

};

#endif /* !__sphere_h__ */

