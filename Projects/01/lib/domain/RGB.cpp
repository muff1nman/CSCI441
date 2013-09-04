/*
 * RGB.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/RGB.h"

RGB::RGB(double r, double g, double b) : Vector_3D(r,g,b) { 
	double max_expected_value = 1.0;
#ifdef LOGGING
	if( r > max_expected_value || g > max_expected_value || b > max_expected_value ) {
		LOG(WARNING) << "One or more RGB values are not in range! Values exceeding 1.0 will be capped at 1.0 (255)";
	}
#endif 

}
