/*
 * Image_2D.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/image_2D.h"

Image_2D::Image_2D( int m, int n ) : m(m), n(n) {
	rgb = new RGB[m*n];
}

RGB& Image_2D::pixel( int i, int j ) {
  return rgb[i+m*j];
}

Image_2D::~Image_2D() {
	delete[] rgb;
}

const RGB& Image_2D::pixel( int index ) const {
	return rgb[index];
}
