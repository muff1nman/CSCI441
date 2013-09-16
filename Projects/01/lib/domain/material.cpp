/*
 * material.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/material.h"

RGB Material::illuminate(const LightSource& light, const Ray& view_ray, double t_of_intersect) const {
	if( in_shadow_at(light, view_ray, t_of_intersect) ) {
		return illuminate_ambient(light);
	} else {
		return illuminate_diffused(light, view_ray, t_of_intersect) + illuminate_specular(light, view_ray, t_of_intersect) + illuminate_ambient(light);
	}
}

Vector_3D Material::light_vector_to_object( const LightSource& light, const Ray& view_ray, double t_of_intersect ) const {
	return light.light_source_location - view_ray.at(t_of_intersect);
}

bool Material::in_shadow_at( const LightSource& light, const Ray& view_ray, double t_of_intersect) const {
	return in_shadow_of_self( light, view_ray, t_of_intersect ) || in_shadow_of_other_primitives( light, view_ray, t_of_intersect );
}

bool Material::in_shadow_of_self( const LightSource& light, const Ray& view_ray, double t_of_intersect) const {
	return light_vector_to_object( light, view_ray, t_of_intersect ) * normal_at(view_ray, t_of_intersect) < 0;
}

bool Material::in_shadow_of_other_primitives( const LightSource& light, const Ray& view_ray, double t_of_intersect) const {
	return false;
}

#ifdef LOGGING
std::string Material::stringify_object() const {
	std::string info = "";
	info += "k_diff: " + k_diff.to_string() + list_sep;
	info += "k_ambient: " + k_ambient.to_string() + list_sep;
	info += "k_specular: " + boost::lexical_cast<std::string>( k_specular ) + list_sep;
	info += "n_specular: " + boost::lexical_cast<std::string>( n_specular ) + sep;
	return info;
}
#endif

Vector_3D Material::halfway_vector( const Vector_3D& viewpoint, const Vector_3D& light_source) const {
	return (viewpoint + light_source) * 0.5;
}

RGB Material::illuminate_diffused(const LightSource& light, const Ray& view_ray, double t_of_intersect) const {
	RGB dif = k_diff * ( normal_at(view_ray, t_of_intersect).normal() * light_vector_to_object( light, view_ray, t_of_intersect ).normal());
	return dif * light.light_source_intensity;
}

RGB Material::illuminate_specular(const LightSource& light, const Ray& view_ray, double t_of_intersect) const {
	double base = halfway_vector( light_vector_to_object( light, view_ray, t_of_intersect ).normal(), -1 * view_ray.direction().normal()).normal() * normal_at(view_ray, t_of_intersect).normal();
	double same_rgb = k_specular * std::pow(base, n_specular);
	same_rgb = same_rgb * light.light_source_intensity;
	return RGB(same_rgb,same_rgb,same_rgb);
}

RGB Material::illuminate_ambient(const LightSource& light) const {
	return k_ambient * light.ambient_intensity;
}
