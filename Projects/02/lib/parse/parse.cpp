/*
 * parse.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "glviewer/parse/parse.h"

#include <iostream>
#include <fstream>

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
	
	e.num_coords_per_vertice = 3;

	std::ifstream ifs(filename);

	size_t num_triangles;
	size_t coord_count;

	size_t verts_per_triangle = 3;

	ifs >> num_triangles >> e.num_vertices;

	e.num_indices = num_triangles * verts_per_triangle;
	coord_count = e.num_vertices * e.num_coords_per_vertice;

	// TODO clean up
	e.indices = new CoordIndex[e.num_indices];
	e.vertices = new Coord[coord_count];

	std::cout << "num ind: " << e.num_indices << std::endl;
	for( size_t i_indice = 0; i_indice < e.num_indices; ++i_indice ) {
		ifs >> e.indices[i_indice];
	}

	for( size_t i_vertex = 0; i_vertex < coord_count; ++i_vertex ) {
		ifs >> e.vertices[i_vertex];
	}

	return e;

}

VectorStream to_vec_stream( const char* filename ) {

	VectorStream s;

	Environment e = parse( filename );
	for( size_t i = 0; i < e.num_indices; i += 3 ) {
		glm::vec3 a(e.vertices[ e.indices[i + 0]*3 + 0 ], e.vertices[ e.indices[i + 0]*3 + 1 ], e.vertices[ e.indices[i + 0]*3 + 2 ] );
		glm::vec3 b(e.vertices[ e.indices[i + 1]*3 + 0 ], e.vertices[ e.indices[i + 1]*3 + 1 ], e.vertices[ e.indices[i + 1]*3 + 2 ] );
		glm::vec3 c(e.vertices[ e.indices[i + 2]*3 + 0 ], e.vertices[ e.indices[i + 2]*3 + 1 ], e.vertices[ e.indices[i + 2]*3 + 2 ] );
		s.push_back(a);
		s.push_back(b);
		s.push_back(c);
	}

	return s;
	
}



