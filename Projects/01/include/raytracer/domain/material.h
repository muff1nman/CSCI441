/*
 * material.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __material_h__
#define __material_h__

#include "raytracer/domain/RGB.h"
#include "raytracer/environment/light_source.h"
#include "raytracer/domain/ray.h"
#include "raytracer/environment/family.h"

#include <cmath>

class Material : public Family, public Logging {
  public:
		Material(const SimpleEnvironment* parent, const RGB& k_diff, const RGB& k_ambient, double k_specular, double n_specular ) : 
			Family(parent), k_diff(k_diff), k_ambient(k_ambient), k_specular(k_specular), n_specular(n_specular) { }

		RGB illuminate(const LightSource& light, const Ray& view_ray, double t_of_intersect) const;

		Vector_3D object_to_light_vector( const LightSource& light, const Ray& view_ray, double t_of_intersect ) const;

		virtual Vector_3D normal_at(const Ray& view_ray, double t_of_intersect) const = 0;

		bool in_shadow_at( const LightSource& light, const Ray& view_ray, double t_of_intersect) const;

#ifdef LOGGING
		std::string stringify_object() const;
#endif

	protected:
    RGB k_diff;
    RGB k_ambient;
    double k_specular;
    double n_specular;

		// TODO put in util?
		Vector_3D halfway_vector( const Vector_3D& viewpoint, const Vector_3D& light_source) const;

		RGB illuminate_diffused(const LightSource& light, const Ray& view_ray, double t_of_intersect) const;

		RGB illuminate_specular(const LightSource& light, const Ray& view_ray, double t_of_intersect) const;

		RGB illuminate_ambient(const LightSource& light) const;

		bool in_shadow_of_self( const LightSource& light, const Ray& view_ray, double t_of_intersect) const;
		
		bool in_shadow_of_other_primitives( const LightSource& light, const Ray& view_ray, double t_of_intersect) const;

};

#endif /* !__material_h__ */

