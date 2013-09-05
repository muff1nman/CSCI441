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

#include <cmath>

class Material {
  public:
		Material(const RGB& k_diff, const RGB& k_ambient, double k_specular, double n_specular ) : 
			k_diff(k_diff), k_ambient(k_ambient), k_specular(k_specular), n_specular(n_specular) { }

		RGB illuminate(const LightSource& light, const Ray& view_ray, double t_of_intersect) const {
			if( in_shadow_at(light, view_ray, t_of_intersect) ) {
				return illuminate_ambient(light);
			} else {
				return illuminate_diffused(light, view_ray, t_of_intersect) + illuminate_specular(light, view_ray, t_of_intersect) + illuminate_ambient(light);
			}
		}

		Vector_3D light_vector_to_object( const LightSource& light, const Ray& view_ray, double t_of_intersect ) const {
			return light.light_source_location - view_ray.at(t_of_intersect);
		}

		virtual Vector_3D normal_at(const Ray& view_ray, double t_of_intersect) const = 0;

		bool in_shadow_at( const LightSource& light, const Ray& view_ray, double t_of_intersect) const {
			return light_vector_to_object( light, view_ray, t_of_intersect ) * normal_at(view_ray, t_of_intersect) < 0;
		}

	protected:
    RGB k_diff;
    RGB k_ambient;
    double k_specular;
    double n_specular;

		// TODO put in util?
		Vector_3D halfway_vector( const Vector_3D& viewpoint, const Vector_3D& light_source) const {
			return (viewpoint + light_source) * 0.5;
		}

		RGB illuminate_diffused(const LightSource& light, const Ray& view_ray, double t_of_intersect) const {
			RGB dif = k_diff * ( normal_at(view_ray, t_of_intersect) * light_vector_to_object( light, view_ray, t_of_intersect ));
			return dif * light.light_source_intensity;
		}

		RGB illuminate_specular(const LightSource& light, const Ray& view_ray, double t_of_intersect) const {
			double same_rgb = k_specular * std::pow(halfway_vector( light_vector_to_object( light, view_ray, t_of_intersect ), view_ray.direction()) * normal_at(view_ray, t_of_intersect), n_specular);
			same_rgb = same_rgb * light.light_source_intensity;
			return RGB(same_rgb,same_rgb,same_rgb);
		}

		RGB illuminate_ambient(const LightSource& light) const {
			return k_ambient * light.ambient_intensity;
		}

};

#endif /* !__material_h__ */

