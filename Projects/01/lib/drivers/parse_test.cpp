/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include <iostream>
#include <cstdlib>

#include "raytracer/parse/parser.h"
#include "raytracer/environment/simple_environment.h"
#include "raytracer/config/config.h"

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

	if( !check_params(argc, argv) ) {
		exit(1);
	}

#ifdef DEBUG
	cout << "DEBUG ON" << endl;
#endif
#ifdef LOG
	cout << "LOG ON" << endl;
#endif

	SimpleEnvironment test = parse(argv[1]);

}
