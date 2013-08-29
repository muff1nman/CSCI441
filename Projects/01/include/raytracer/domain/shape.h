/*
 * shape.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __shape_h__
#define __shape_h__

#include "raytracer/intersection/intersectee.h"

class Shape : public Intersectee {
	private:
		int ID;

	public:
		Shape(int ID) : ID(ID) { }

		int get_ID() const { return ID; }
};

#endif /* !__shape_h__ */

