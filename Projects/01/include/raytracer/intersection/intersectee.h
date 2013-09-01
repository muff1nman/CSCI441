/*
 * intersectee.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __intersectee_h__
#define __intersectee_h__

#include "raytracer/domain/ray.h"
#include <boost/optional.hpp>

/**
 * An abstract class for adding the capability for a shape to know if it is
 * intersected.
 */
class Intersectee {

	public:
		virtual bool is_intersected( Ray r ) const = 0;

		virtual boost::optional<double> intersected_at( Ray r ) const = 0;

};
#endif /* !__intersectee_h__ */

