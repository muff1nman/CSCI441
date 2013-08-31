/*
 * sphere.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __sphere_h__
#define __sphere_h__

#include "raytracer/util/logging.h"
#include "raytracer/domain/vector_3D.h"

class Sphere : public Logging {

	public:
		Sphere( const Vector_3D& center, double radius ) : center(center), radius(radius) { }

#ifdef LOGGING
		std::string to_string() {
			std::string info = "";
			info += nested_start;
			{
				info += "radius: " + boost::lexical_cast<std::string>(radius) + list_sep;
				info += "center: " + this->center.to_string() + sep;
			}
			info += nested_finish;
			return info;
		}
#endif

	private:
		Vector_3D center;
		double radius;

}

#endif /* !__sphere_h__ */

