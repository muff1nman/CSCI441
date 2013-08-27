/*
 * image_2D.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __image_2D_h__
#define __image_2D_h__

#include "raytracer/domain/RGB.h"

class image_2D {
	public:
		image_2D( int m, int n );

		RGB& pixel( int i, int j );

		void save_to_ppm_file( char* filename );

};

#endif /* !__image_2D_h__ */

