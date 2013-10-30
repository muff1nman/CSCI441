/*
 * environment.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __environment_h__
#define __environment_h__

#include "glviewer/types.h"

class Environment {
	public:
		CoordBuffer vertices;
		CoordIndexBuffer indices;

		size_t num_vertices;
		size_t num_coords_per_vertice;
		size_t num_indices;

};

#endif /* !__environment_h__ */

