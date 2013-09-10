/*
 * shape.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __shape_h__
#define __shape_h__

#include "raytracer/intersection/intersectee.h"
#include "raytracer/domain/material.h"
#include "raytracer/util/logging.h"

class Shape : public Intersectee, public Material {
	public:
		Shape(const RGB& k_diff, const RGB& k_ambient, double k_specular, double n_specular ) : Material(k_diff, k_ambient, k_specular, n_specular ) { }

		virtual Shape* clone() const = 0;

		virtual ~Shape() { }
};

#endif /* !__shape_h__ */

