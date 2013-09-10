/*
 * simple_worker.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/environment/simple_worker.h"

void SimpleWorker::operator()() {
	SimpleEnvironment::create_image_interal(img, shapes, start, stop_before, light);
}



