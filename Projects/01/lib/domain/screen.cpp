/*
 * screen.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/screen.h"

ScreenIterator Screen::begin() const { 
	return ScreenIterator(this);
}

ScreenIterator Screen::end() const {
	return ScreenIterator(this, 0, resolution_y );
}

#ifdef LOGGING
std::string Screen::to_string() {
	std::string info(nested_start);
	{
		info += "res x: " + boost::lexical_cast<std::string>( resolution_x ) + list_sep;
		info += "res y: " + boost::lexical_cast<std::string>( resolution_y ) + list_sep;
		info += "horizontal vector: " + this->horizontal.to_string() + list_sep;
		info += "vertical vector: " + this->vertical.to_string() + list_sep;
		info += "lower left corner: " + this->lower_left_corner.to_string() + sep;
	}
	info += nested_finish;
	return info;
}
#endif
