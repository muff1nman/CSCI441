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
#include "raytracer/config/config.h"
#include "raytracer/domain/screen.h"

#ifdef LOGGING
#include <string>
#endif

struct Config {

	Config(
			const Vector_3D& viewpoint,
			const Screen& screen,
			const RGB& light_source_color,
			double light_source_intensity,
			double ambient_light_intensity,
			int number_of_primitives) : 
		viewpoint( viewpoint ),
		screen( screen ),
		light_source_color( light_source_color ),
		light_source_intensity( light_source_intensity ),
		ambient_light_intensity( ambient_light_intensity ),
		number_of_primitives( number_of_primitives ) { }

	Vector_3D viewpoint;

	Screen screen;

	RGB light_source_color;

	double light_source_intensity;
	double ambient_light_intensity;

	int number_of_primitives;

#ifdef LOGGING
	std::string to_string();
#endif

};

#endif /* !__config_h__ */

