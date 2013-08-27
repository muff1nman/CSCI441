/*
 * image_2D.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/image_2D.h"


image_2D::image_2D( int m, int n ) : m(m), n(n) {
	rgb = new RGB[m*n];
}

RGB& image_2D::pixel( int i, int j ) {
  return rgb[i+m*j];
}

image_2D::~image_2D() {
	// TODO
}
