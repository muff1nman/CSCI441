/*
 * find_intersections.cpp
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
#include "common.h"

#include <vector>
#include <iostream>

using namespace std;

Vector_3D prompt_for_vector() {
	double x,y,z;
	cout << "x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	cout << "z: ";
	cin >> z;
	return Vector_3D(x,y,z);
}

int main(int argc, char** argv) {
	cout << "Ray Tracer" << endl;
	cout << "  -- Andrew DeMaria" << endl;

	init();

	if( !check_params(argc, argv) ) {
		exit(1);
	}

	SimpleEnvironment test = parse(argv[1]);

	Vector_3D start, finish;
	start = prompt_for_vector();
	finish = prompt_for_vector();

	Ray user_ray( start, finish );

	cout << "Does ray intersect any shapes?" << endl;
	boost::optional<int> shape_id = test.closest_intersection( user_ray );

	if(shape_id) {
		cout << "Intersected shape is: " << *shape_id << endl;
	} else {
		cout << "There was no shape intersected" << endl;
	}

}
