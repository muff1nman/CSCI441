/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include <iostream>
#include "raytracer/parse/parser.h"

using namespace std;

int main() {
	cout << "Ray Tracer" << endl;
	cout << "  -- Andrew DeMaria" << endl;

	cout << endl;

	parse("Hello");
}

