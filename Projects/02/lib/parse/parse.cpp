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
	//e.vertices = square_vertices_a;
	//e.indices = square_indices_a;
	//e.num_vertices = 4;
	//e.num_indices = 6;

	// TODO
	
	e.num_coords_per_vertice = 3;

	std::ifstream ifs(filename);

	size_t num_triangles;
	size_t coord_count;

	ifs >> num_triangles >> e.num_vertices;

	e.num_indices = num_triangles * e.num_coords_per_vertice;
	coord_count = e.num_vertices * e.num_coords_per_vertice;

	std::cout << "Num triangles: " << num_triangles << std::endl;
	std::cout << "num vertices: " << e.num_vertices << std::endl;

	e.indices = new CoordIndex[e.num_indices];
	e.vertices = new Coord[coord_count];

	for( size_t i_indice = 0; i_indice < e.num_indices; ++i_indice ) {
		ifs >> e.indices[i_indice];
		std::cout << "index: " << e.indices[i_indice] << std::endl;
	}

	for( size_t i_vertex = 0; i_vertex < coord_count; ++i_vertex ) {
		ifs >> e.vertices[i_vertex];
		std::cout << "Vertex: " << e.vertices[i_vertex] << std::endl;
	}

	return e;

}


