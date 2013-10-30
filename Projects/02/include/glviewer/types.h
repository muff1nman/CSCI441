/*
 * types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __types_h__
#define __types_h__

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <vector>

typedef GLfloat Coord;

typedef Coord* CoordBuffer;

typedef GLuint CoordIndex;
typedef CoordIndex* CoordIndexBuffer;

typedef std::vector<glm::vec3> VectorStream;


#endif /* !__types_h__ */

