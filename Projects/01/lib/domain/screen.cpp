/*
 * screen.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/screen.h"


Screen::Screen( 
		const Vector_3D& viewpoint,
		const Vector_3D& lower_left,
		const Vector_3D& horizontal,
		const Vector_3D& vertical,
		int x,
		int y) :
	viewpoint( viewpoint ),
	lower_left_corner( lower_left ),
	horizontal( horizontal ),
	vertical( vertical ),
	resolution_x( x ),
	resolution_y( y ) {
		this->upper_left_corner = this->lower_left_corner + this->vertical;
	}

ScreenIterator Screen::begin() const { 
	return ScreenIterator(this);
}

ScreenIterator Screen::end() const {
	return ScreenIterator(this, 0, resolution_y );
}

Image_2D Screen::blank_image() const {
	return Image_2D( this->resolution_x, this->resolution_y );
}

#ifdef LOGGING
std::string Screen::to_string() {
	std::string info(nested_start);
	{
		info += "res x: " + boost::lexical_cast<std::string>( resolution_x ) + list_sep;
		info += "res y: " + boost::lexical_cast<std::string>( resolution_y ) + list_sep;
		info += "viewpoint: " + this->viewpoint.to_string() + list_sep;
		info += "horizontal vector: " + this->horizontal.to_string() + list_sep;
		info += "vertical vector: " + this->vertical.to_string() + list_sep;
		info += "lower left corner: " + this->lower_left_corner.to_string() + list_sep;
		info += "upper left corner: " + (this->lower_left_corner + this->vertical ).to_string() + list_sep;
		info += "upper right corner: " + (this->lower_left_corner + this->vertical + this->horizontal ).to_string() + list_sep;
		info += "lower right corner: " + (this->lower_left_corner + this->horizontal ).to_string() + sep;
	}
	info += nested_finish;
	return info;
}
#endif
