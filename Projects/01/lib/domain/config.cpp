/*
 * config.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/config.h"

#ifdef LOGGING
#include <boost/lexical_cast.hpp>
#endif

#ifdef LOGGING
std::string Config::to_string() {
	std::string info = std::string("") + sep + nested_start;
	{
		info += "primitives: " + boost::lexical_cast<std::string>(this->number_of_primitives) + list_sep;
		info += "ambient_light_intensity: " + boost::lexical_cast<std::string>(this->ambient_light_intensity) + list_sep;
		info += "light_source_intensity: " + boost::lexical_cast<std::string>(this->light_source_intensity) + list_sep;
		info += std::string("light_source_color: ") + this->light_source_color.to_string() + list_sep;
		info += "screen: " + this->screen.to_string() + sep;
	}
	info += nested_finish;
	
	return info;
}

#endif


