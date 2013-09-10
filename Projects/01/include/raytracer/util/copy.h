/*
 * copy.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __copy_h__
#define __copy_h__

#include "raytracer/domain/shapes/shape.h"

#include <vector>

std::vector<Shape* > deep_copy( const std::vector< const Shape* >& other ) {
	std::vector<Shape* > to_return(other.size());
	// TODO	
	return to_return;
}

#endif /* !__copy_h__ */

