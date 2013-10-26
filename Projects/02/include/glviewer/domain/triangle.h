/*
 * Triangle.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __Triangle_h__
#define __Triangle_h__

#include "types.h"

class Triangle {
	public:
		Triangle(CoordIndex a, CoordIndex b, CoordIndex c ) : a(a), b(b), c(c) { }
		CoordIndex a, b, c;
}

#endif /* !__Triangle_h__ */

