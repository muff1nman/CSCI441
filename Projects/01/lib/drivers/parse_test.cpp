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

int main(int argc, char** argv) {
	cout << "Ray Tracer" << endl;
	cout << "  -- Parsing" << endl;
	cout << "  -- Andrew DeMaria" << endl;

	init();

	if( !check_params(argc, argv) ) {
		exit(1);
	}

	SimpleEnvironment* test = parse(argv[1]);

#ifdef LOGGING
	test->log_state();
#endif

	delete test;

}
