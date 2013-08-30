/*
 * parser.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/parse/parser.h"
#include "raytracer/domain/config.h"
#include "raytracer/domain/vector_3D.h"
#include "raytracer/domain/RGB.h"


// TODO return pointer instead?
SimpleEnvironment parse( const char* filename ) {
	std::ifstream ifs(filename);
	assert(ifs);

	int resolution_x;
	int resolution_y;
	double viewpoint[3];
	double screen_lower_left_corner[3];
	double screen_horizontal_vector[3];
	double screen_vertical_vector[3];
	double light_source[3];
	double light_intensity;
	double ambient_light_intensity;
	int number_of_primitives;

	ifs >> resolution_x >> resolution_y;
	ifs >> viewpoint[0] >> viewpoint[1] >> viewpoint[2];
	ifs >> screen_lower_left_corner[0] >> screen_lower_left_corner[1] >> screen_lower_left_corner[2];
	ifs >> screen_horizontal_vector[0] >> screen_horizontal_vector[1] >> screen_horizontal_vector[2];
	ifs >> screen_vertical_vector[0] >> screen_vertical_vector[1] >> screen_vertical_vector[2];
	ifs >> light_source[0] >> light_source[1] >> light_source[2];
	ifs >> light_intensity;
	ifs >> ambient_light_intensity;
	ifs >> number_of_primitives;

	Config conf;
	conf.resolution_x = resolution_x;
	conf.resolution_y = resolution_y;

	Vector_3D viewpoint_vector(viewpoint[0], viewpoint[1], viewpoint[2]);
	conf.viewpoint = viewpoint_vector;

	Vector_3D screen_lower_left_corner_vector(
			screen_lower_left_corner[0],
			screen_lower_left_corner[1],
			screen_lower_left_corner[2]);
	conf.screen_lower_left_corner = screen_lower_left_corner_vector;

	Vector_3D screen_horizontal_vector_vector(
			screen_horizontal_vector[0],
			screen_horizontal_vector[1],
			screen_horizontal_vector[2]);
	conf.screen_horizontal = screen_horizontal_vector_vector;

	Vector_3D screen_vertical_vector_vector(
			screen_vertical_vector[0],
			screen_vertical_vector[1],
			screen_vertical_vector[2]);
	conf.screen_vertical = screen_vertical_vector_vector;

	RGB light_source_rgb(light_source[0], light_source[1], light_source[2]);
	conf.light_source_color = light_source_rgb;

	conf.light_source_intensity = light_intensity;

	conf.ambient_light_intensity = ambient_light_intensity;

	conf.number_of_primitives = number_of_primitives;

	SimpleEnvironment env(conf);

	for ( int i=0; i<number_of_primitives; i++ ) {
		char primitive_type;
		ifs >> primitive_type;
		switch(primitive_type) {
			case 's':
			case 'S':
				{
					double center[3];
					double radius;
					double k_diffuse[3];
					double k_ambient[3];
					double k_specular;
					double n_specular;

					ifs >> center[0] >> center[1] >> center[2];
					ifs >> radius;
					ifs >> k_diffuse[0] >> k_diffuse[1] >> k_diffuse[2];
					ifs >> k_ambient[0] >> k_ambient[1] >> k_ambient[2];
					ifs >> k_specular >> n_specular;

					// add the sphere to your datastructures (primitive list, sphere list or such) here
					// TODO
				}
				break;
			case 'T':
			case 't':
				{
					double a1[3];
					double a2[3];
					double a3[3];
					double k_diffuse[3];
					double k_ambient[3];
					double k_specular;
					double n_specular;

					ifs >> a1[0] >> a1[1] >> a1[2];
					ifs >> a2[0] >> a2[1] >> a2[2];
					ifs >> a3[0] >> a3[1] >> a3[2];
					ifs >> k_diffuse[0] >> k_diffuse[1] >> k_diffuse[2];
					ifs >> k_ambient[0] >> k_ambient[1] >> k_ambient[2];
					ifs >> k_specular >> n_specular; 	    

					// add the triangle to your datastructure (primitive list, sphere list or such) here
					// TODO
				}
				break;
			default:
				assert(0);
		} // End switch
	} // End for

	return env;

} // End parse

