/*
 * simple_environment.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/environment/simple_environment.h"

#ifdef LOGGING
std::string SimpleEnvironment::to_string() {
	std::string info = "SimpleEnv: \n";
	info += this->config.to_string();
	return info;
}

void SimpleEnvironment::log_state() {
	LOG(INFO) << this->to_string();
}
#endif
