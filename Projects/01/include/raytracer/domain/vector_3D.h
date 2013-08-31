/*
 * vector_3D.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __vector_3D_h__
#define __vector_3D_h__

#include "raytracer/util/logging.h"

class Vector_3D : public Logging {

	public:
		Vector_3D(double x = 0.0, double y = 0.0, double z = 0.0 ) : x(x), y(y), z(z) { }

		//void set_x(double x) { this->x = x; }
		//void set_y(double y) { this->y = y; }
		//void set_z(double z) { this->z = z; }

		double get_x() const { return x; }
		double get_y() const { return y; }
		double get_z() const { return z; }

#ifdef LOGGING
		std::string to_string() {
			std::string info = "";
			info += nested_start;
			{
				info += "x: " + boost::lexical_cast<std::string>(x) + list_sep;
				info += "y: " + boost::lexical_cast<std::string>(y) + list_sep;
				info += "z: " + boost::lexical_cast<std::string>(z) + sep;
			}
			info += nested_finish;
			return info;
		}
#endif

	private:
		double x, y, z;

};

#endif /* !__vector_3D_h__ */

