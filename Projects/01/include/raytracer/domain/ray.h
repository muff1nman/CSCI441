/*
 * ray.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __ray_h__
#define __ray_h__

#include "raytracer/domain/vector_3D.h"

class Ray {
	public:
		Ray(const Vector_3D& start, const Vector_3D& end) :  start(start), end(end) { }

		const Vector_3D& get_start() const { return start; }
		const Vector_3D& get_end() const { return end; }

	private:
		Vector_3D start;
		Vector_3D end;

};

#endif /* !__ray_h__ */

