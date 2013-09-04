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
#include <boost/lexical_cast.hpp>
#endif

struct Config {

	Config(
			const Screen& screen,
			const Vector_3D& light_source_location,
			double light_source_intensity,
			double ambient_light_intensity,
			int number_of_primitives) : 
		screen( screen ),
		light_source_location( light_source_location ),
		light_source_intensity( light_source_intensity ),
		ambient_light_intensity( ambient_light_intensity ),
		number_of_primitives( number_of_primitives ) { }

	Screen screen;

	Vector_3D light_source_location;

	double light_source_intensity;
	double ambient_light_intensity;

	int number_of_primitives;


#ifdef LOGGING
	std::string to_string() {
		std::string info = std::string("") + sep + nested_start;
		{
			info += "primitives: " + boost::lexical_cast<std::string>(this->number_of_primitives) + list_sep;
			info += "ambient_light_intensity: " + boost::lexical_cast<std::string>(this->ambient_light_intensity) + list_sep;
			info += "light_source_intensity: " + boost::lexical_cast<std::string>(this->light_source_intensity) + list_sep;
			info += std::string("light_source_location: ") + this->light_source_location.to_string() + list_sep;
			info += "screen: " + this->screen.to_string() + sep;
		}
		info += nested_finish;

		return info;
	}
#endif

};

#endif /* !__config_h__ */

