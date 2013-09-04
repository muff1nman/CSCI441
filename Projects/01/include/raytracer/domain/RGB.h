/*
 * RGB.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __RGB_h__
#define __RGB_h__

#include "raytracer/domain/vector_3D.h"

class RGB : public Vector_3D {

	public:
		RGB(double r, double g, double b);
		RGB() : Vector_3D(0,0,0) { }

		static const int MAX_COLOR = 256;

		double r() const { return x; }
		double g() const { return y; }
		double b() const { return z; }

		// TODO possibly remove if the only thing that needs these functions are
		// test drivers
		void set_r(double r) { this->x = r; }
		void set_g(double g) { this->y = g; }
		void set_b(double b) { this->z = b; }

};

#endif /* !__RGB_h__ */

