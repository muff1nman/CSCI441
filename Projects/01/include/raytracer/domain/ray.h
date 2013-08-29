/*
 * ray.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __ray_h__
#define __ray_h__

#include "raytracer/domain/vector.h"

class Ray {
	public:
		Ray(const Vector& start, const Vector& end) :  start(start), end(end) { }

		const Vector& get_start() const { return start; }
		const Vector& get_end() const { return end; }

	private:
		Vector start;
		Vector end;

};

#endif /* !__ray_h__ */

