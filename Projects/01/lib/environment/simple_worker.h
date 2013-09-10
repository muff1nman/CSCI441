/*
 * simple_worker.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __simple_worker_h__
#define __simple_worker_h__

#include "raytracer/util/worker.h"
#include "raytracer/domain/image_2D.h"
#include "raytracer/util/copy.h"
#include "raytracer/environment/screen_iterator.h"
#include "raytracer/environment/light_source.h"

class SimpleWorker : public Worker { 

	public:

		SimpleWorker(Image_2D* img, const LightSource& light, const ScreenIterator& start, const ScreenIterator& stop_before, const std::vector<const Shape*>& shapes) : img(img), light(light), start(start), stop_before(stop_before) {
			this->shapes = deep_copy( shapes );

		}

		~SimpleWorker() {
			// TODO delete shapes
		}

		void operator()() {
			// TODO work here
		}

	private:
		Image_2D* img;
		LightSource light;
		ScreenIterator start;
		ScreenIterator stop_before;
		
		std::vector<Shape*> shapes;

}

#endif /* !__simple_worker_h__ */

