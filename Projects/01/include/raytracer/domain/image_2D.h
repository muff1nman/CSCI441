/*
 * image_2D.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __image_2D_h__
#define __image_2D_h__

#include "raytracer/domain/RGB.h"
#include <cstddef>

class image_2D {
	public:
		image_2D( int m, int n );

		RGB& pixel( int i, int j );

		RGB& pixel( int index );

		int x_size() { return m; }
		int y_size() { return n; }

		~image_2D();

	private:
		RGB* rgb;
		int m;
		int n;

};

#endif /* !__image_2D_h__ */

