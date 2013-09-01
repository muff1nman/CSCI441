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
		Ray(const Vector_3D& start, const Vector_3D& end) :  start(start), end(end) { }

		const Vector_3D& get_start() const { return start; }
		const Vector_3D& get_end() const { return end; }

		Vector_3D direction() const;

		Vector_3D origin() const { return start; }

#ifdef LOGGING
		std::string to_string() {
			std::string info(nested_start);
			{
				info += this->start.to_string() + list_sep;
				info += this->end.to_string() + sep;
			}
			info += nested_finish;
			return info;
		}
#endif

	private:
		Vector_3D start;
		Vector_3D end;

};

#endif /* !__ray_h__ */

