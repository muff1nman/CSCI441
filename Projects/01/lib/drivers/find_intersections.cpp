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

#include "raytracer/domain/ray.h"
#include "raytracer/domain/shape.h"
#include "raytracer/intersection/util.h"

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

int main() {
	cout << "Ray Tracer" << endl;
	cout << "  -- Andrew DeMaria" << endl;
	Vector_3D start, finish;
	start = prompt_for_vector();
	finish = prompt_for_vector();

	Ray user_ray( start, finish );
	vector<Shape> shape_list;

	cout << "Does ray intersect any shapes?" << endl;
	cout << closest_intersection( user_ray, shape_list);

}
