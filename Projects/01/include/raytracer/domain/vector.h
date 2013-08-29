/*
 * vector.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __vector_h__
#define __vector_h__

class Vector_3D {

	public:
		Vector_3D(double x, double y, double z ) : x(x), y(y), z(z) { }

		double get_x() const { return x; }
		double get_y() const { return y; }
		double get_z() const { return z; }

	private:
		double x, y, z;

};

#endif /* !__vector_h__ */

