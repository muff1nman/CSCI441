/*
 * RGB.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __RGB_h__
#define __RGB_h__

#include "raytracer/config/config.h"

#ifdef LOGGING
#include <string>
#endif

struct RGB {
	RGB( double r = 0.0, double g = 0.0, double b = 0.0 ) : r(r), g(g), b(b) { }
	double r, g, b; 

#ifdef LOGGING
	std::string to_string();
#endif
};

#endif /* !__RGB_h__ */

