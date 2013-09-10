/*
 * simple_worker.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __simple_worker_h__
#define __simple_worker_h__

#include "raytracer/util/worker.h"
#include "raytracer/util/logging.h"
#include "raytracer/domain/image_2D.h"
#include "raytracer/util/copy.h"
#include "raytracer/environment/screen_iterator.h"
#include "raytracer/environment/light_source.h"
#include "raytracer/environment/simple_environment.h"

class SimpleWorker : public Worker, public Logging { 

	public:

		SimpleWorker(Image_2D* img, const LightSource& light, const ScreenIterator& start, const ScreenIterator& stop_before, const std::vector<Shape*>& shapes) : img(img), light(light), start(start), stop_before(stop_before) {
			this->shapes = std::vector<Shape*>(shapes.size());
			for( const Shape* s : shapes ) {
#ifdef LOGGING
				LOG(INFO) << "duplicating shapes";
#endif
				this->shapes.push_back( s->clone() );
			}
		}

		~SimpleWorker() {
			// TODO call from simple env instead
			for( Shape* ptr : this->shapes ) {
				delete ptr;
			}
		}

		void operator()();

	private:
		Image_2D* img;
		LightSource light;
		ScreenIterator start;
		ScreenIterator stop_before;
		
		std::vector<Shape*> shapes;

};

#endif /* !__simple_worker_h__ */

