/*
 * point.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __point_h__
#define __point_h__

#include "type.h"

class Point {
	public:
		Point( CoordType x, CoordType y, CoordType z ) : x(x), y(y), z(z) { }
		CoordType x, y, z;
};

#endif /* !__point_h__ */

