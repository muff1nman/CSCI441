/*
 * parse.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "glviewer/parse/parse.h"

GLfloat square_vertices_a[] = {
  -1, -1, 0,
  -1,  1, 0,
   1,  1, 0,
   1, -1, 0 
};

GLuint square_indices_a[] = {
  0, 1, 2,   // indices into the vertices of the first triangle
  0, 2, 3    // ... and second triangle (with consistent orientation)
};


Environment parse( const char* filename ) {
	Environment e;
	e.vertices = square_vertices_a;
	e.indices = square_indices_a;
	e.num_vertices = 4;
	e.num_coords_per_vertice = 3;
	e.num_indices = 6;

	// TODO

	return e;

}


