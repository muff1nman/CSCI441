/*
 * Image_2D.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __Image_2D_h__
#define __Image_2D_h__

#include "raytracer/domain/RGB.h"
#include <cstddef>

class Image_2D {
	public:
		Image_2D( int m, int n );

		RGB& pixel( int i, int j ) const;

		void set(int i, int j, const RGB& rgb);

		const RGB& pixel( int index ) const;

		RGB& pixel( int index );

		int x_size() const { return m; }
		int y_size() const { return n; }

		~Image_2D();

	private:
		RGB* rgb;
		int m;
		int n;

};

#endif /* !__Image_2D_h__ */

