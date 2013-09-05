/*
 * light_source.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __light_source_h__
#define __light_source_h__

#include "raytracer/util/logging.h"

struct LightSource {

	Vector_3D light_source_location;
	double light_source_intensity;
	double ambient_intensity;

};

#endif /* !__light_source_h__ */

