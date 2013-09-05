/*
 * ray.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __ray_h__
#define __ray_h__

#include "raytracer/domain/vector_3D.h"
#include "raytracer/config/config.h"
#include "raytracer/util/logging.h"

class Ray : public Logging {
	public:
		// TODO check that we are not passing in a direction to end ever
		Ray(const Vector_3D& start, const Vector_3D& end) :  start(start) {
			this->_direction = (end - this->start).normal();
		}

		const Vector_3D& get_start() const { return start; }

		Vector_3D direction() const { return _direction; }

		Vector_3D origin() const { return start; }

		Vector_3D at(double some_time);

#ifdef LOGGING
		std::string to_string() const {
			std::string info(nested_start);
			{
				info += "start: " + this->start.to_string() + list_sep;
				info += "direction: " + this->_direction.to_string() + sep;
			}
			info += nested_finish;
			return info;
		}
#endif

	private:
		Vector_3D start;
		Vector_3D _direction;

};

#endif /* !__ray_h__ */

