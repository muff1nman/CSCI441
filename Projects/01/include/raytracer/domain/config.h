/*
 * config.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __config_h__
#define __config_h__

#include "raytracer/domain/RGB.h"
#include "raytracer/domain/vector_3D.h"

#include <string>

struct Config {

	Vector_3D viewpoint;
	Vector_3D screen_lower_left_corner;
	Vector_3D screen_vertical;
	Vector_3D screen_horizontal;

	int resolution_x;
	int resolution_y;

	RGB light_source_color;

	double light_source_intensity;
	double ambient_light_intensity;

	int number_of_primitives;

	std::string to_string();


};

#endif /* !__config_h__ */

