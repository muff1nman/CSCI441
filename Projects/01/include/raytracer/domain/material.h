/*
 * material.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __material_h__
#define __material_h__

#include "raytracer/domain/RGB.h"

class Material {
  public:
		virtual RGB illuminate(const Vector_3D& light_source_location, double light_source_intensity, const Vector_3D view_direction) const = 0 ;

	private:
    RGB k_diff;
    RGB k_ambient;
    double k_specular;
    double n_specular;
};

#endif /* !__material_h__ */

