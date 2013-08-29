/*
 * image_output.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/output/image_output.h"
#include "util.h"

void save_to_ppm_file( const Image_2D& image, const char* filename ) {
	std::ofstream ofs(filename,std::ios::binary);
	assert(ofs);
	ofs << "P6" << std::endl;
	ofs << image.x_size() << " " << image.y_size() << std::endl << 255 << std::endl;
	for ( int i=0; i<image.x_size()*image.y_size(); i++ )
	{
		unsigned char r = clampnround(256*image.pixel(i).r);
		unsigned char g = clampnround(256*image.pixel(i).g);
		unsigned char b = clampnround(256*image.pixel(i).b);
		ofs.write((char*)&r,sizeof(char));
		ofs.write((char*)&g,sizeof(char));
		ofs.write((char*)&b,sizeof(char));
	}
}


