/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */
#include "raytracer/parse/parser.h"
#include "raytracer/environment/simple_environment.h"
#include "raytracer/config/config.h"
#include "common.h"

#include <iostream>
#include <cstdlib>

using namespace std;

bool check_params(int argc, char** argv) {
	if( argc != 2 ) {
		return false;
	}
	return true;
}


int main(int argc, char** argv) {
	cout << "Ray Tracer" << endl;
	cout << "  -- Parsing" << endl;
	cout << "  -- Andrew DeMaria" << endl;

	init();

	if( !check_params(argc, argv) ) {
		exit(1);
	}

	SimpleEnvironment test = parse(argv[1]);

}
