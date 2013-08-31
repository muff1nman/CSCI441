/*
 * simple_environment.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/environment/simple_environment.h"
#include <iostream>

std::string SimpleEnvironment::to_string() {
	std::string info = "SimpleEnv: ";

	return info;
}

#ifdef LOGGING
void SimpleEnvironment::log_state() {
	LOG(INFO) << this->to_string();
}
#endif
