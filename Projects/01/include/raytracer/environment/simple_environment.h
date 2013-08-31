/*
 * simple_environment.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __simple_environment_h__
#define __simple_environment_h__

#include "raytracer/environment/environment.h"
#include "raytracer/config/config.h"
#include "raytracer/domain/config.h"
#include "raytracer/domain/shapes/shape.h"

#ifdef LOGGING
#include <glog/logging.h>
#include <string>
#endif

#include <vector>

class SimpleEnvironment : public Environment {
	public:
		SimpleEnvironment(const Config& config) : config(config) { /*TODO*/ }

		~SimpleEnvironment();

		void add_shape(Shape* shape);


#ifdef LOGGING
		void log_state();
#endif

	private:
		Config config;
		std::vector<Shape*> shapes;

#ifdef LOGGING
		std::string to_string();
#endif

};

#endif /* !__simple_environment_h__ */

