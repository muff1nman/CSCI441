/*
 * RGB.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/RGB.h"

#ifdef LOGGING
#include <boost/lexical_cast.hpp>
#endif

#ifdef LOGGING
	std::string RGB::to_string() {
		std::string info = "";
		info += nested_start;
		{
			info += "r: " + boost::lexical_cast<std::string>(this->r) + list_sep;
			info += "g: " + boost::lexical_cast<std::string>(this->g) + list_sep;
			info += "b: " + boost::lexical_cast<std::string>(this->b) + sep;
		}
		info += nested_finish;
		return info;
	}
#endif


