/*
 * simple image.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

/** 
 * The goal here is to implement part one of the ray tracing lab 
 *
 * The algorithm can be described here:
 *
 * for ( x=0; x<resolution_x; x++ )
 *   for ( y=0; y<resolution_y; y++ )
 *     ray r = EyeRay(x,y);
 *     (t,pid) := ClosestIntersection(r);
 *     if (t==-1) then use 0,0,0 as the R,G and B values
 *        else use diffuse RGB components of MaterialOf(pid)
 *   endfor
 * endfor
 *
 */

#include "raytracer/config/config.h"
#include "raytracer/domain/ray.h"
#include "raytracer/parse/parser.h"
#include "raytracer/environment/simple_environment.h"
#include "raytracer/domain/image_2D.h"
#include "raytracer/output/image_output.h"
#include "common.h"

#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	cout << "Ray Tracer" << endl;
	cout << "  -- Andrew DeMaria" << endl;

	init();

	if( !check_params(argc, argv) ) {
#ifdef LOGGING
		LOG(FATAL) << "Invalid arguments";
#endif
		exit(1);
	}

	string input_file = input_file_name(argc, argv);

	cout << "Processing " << input_file << endl;

	SimpleEnvironment* test = parse(input_file.c_str());

	Vector_3D start = prompt_for_vector();
	Vector_3D finish = prompt_for_vector();
	Ray r(start, finish);
	boost::optional<const Shape*> intersect = test->closest_intersection( r );

	if( intersect ) {
		cout << "Intersected!" << endl;
	} else {
		cout <<  "No intersection" << endl;
	}

/*
 *  Image_2D img = test.create_image();
 *
 *  save_to_ppm_file(img, output_file_name(argc, argv).c_str());
 */

	delete test;

}
