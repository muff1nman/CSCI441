/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/parse/parser.h"
#include "raytracer/domain/image_2D.h"
#include "raytracer/output/image_output.h"

#include <iostream>

using namespace std;

int main() {
	cout << "Ray Tracer" << endl;
	cout << "  -- Andrew DeMaria" << endl;

	//parse( "random file name" );

	int resolution_x = 500, resolution_y = 500;

	image_2D img(resolution_x,resolution_y);
	for ( int x=0; x<resolution_x; x++ ) {
		for ( int y=0; y<resolution_y; y++ )
		{
			RGB& pix = img.pixel(x,y);

			/* 
				 call your raytracer here
				 then assign the rgb values
				 it returns to the pixel 
				 */

			// this is just to produce a fun image...
			pix.r = 0.5+0.5*sin(sin(x/30.0)+y*y/700.0);
			pix.g = 0.5+0.5*sin(y/71.0);
			pix.b = 0.5+0.5*sin(x*x*x/120000.0+y*y/1700.0);
		} // End inner For
	} // End For

	save_to_ppm_file(img, "output.ppm");

}

