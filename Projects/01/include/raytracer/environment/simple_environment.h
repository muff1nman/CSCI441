/*
 * simple_environment.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __simple_environment_h__
#define __simple_environment_h__

#include "raytracer/environment/environment.h"
#include "raytracer/domain/config.h"

class SimpleEnvironment : public Environment {
	public:
		SimpleEnvironment(const Config& config) : config(config) { /*TODO*/ }

	private:
		Config config;
};

#endif /* !__simple_environment_h__ */

