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

class Material {
  public:
		Material(const RGB& k_diff, const RGB& k_ambient, double k_specular, double n_specular ) : 
			k_diff(k_diff), k_ambient(k_ambient), k_specular(k_specular), n_specular(n_specular) { }

		virtual RGB illuminate(const LightSource& light, const Vector_3D view_direction) const = 0;

	protected:
    RGB k_diff;
    RGB k_ambient;
    double k_specular;
    double n_specular;
};

#endif /* !__material_h__ */

