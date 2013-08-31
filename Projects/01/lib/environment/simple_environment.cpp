/*
 * simple_environment.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/environment/simple_environment.h"

void SimpleEnvironment::~SimpleEnvironment() {

	// deallocate each shape
	for( Shape* ptr : this->shapes ) {
		delete ptr;
	}
}

void SimpleEnvironment::add_shape(Shape* shape) {
	this->shapes.push_back( shape );
}

#ifdef LOGGING
std::string SimpleEnvironment::to_string() {
	std::string info = "";
	info += nested_start;
	{
	info += "config: " + this->config.to_string() + sep;
	}
	info += nested_finish;
	return info;
}

void SimpleEnvironment::log_state() {
	LOG(INFO) << "SimpleEnv: " + this->to_string();
}
#endif
