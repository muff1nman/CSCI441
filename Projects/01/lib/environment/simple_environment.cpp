/*
 * simple_environment.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/environment/simple_environment.h"


SimpleEnvironment::~SimpleEnvironment() {

	// deallocate each shape
	for( Shape* ptr : this->shapes ) {
		delete ptr;
	}
}

void SimpleEnvironment::add_shape(Shape* shape) {
	this->shapes.push_back( shape );
}

static boost::optional<const Shape*> closest_intersection_internal( const Ray& ray, const std::vector<Shape*>& shapes ) {
	boost::optional<const Shape*> shape;
	boost::optional<double> closest_intersected_time;
	boost::optional<double> tested_time;
	for( Shape* s : shapes ) {
#ifdef LOGGING
		LOG(INFO) << "Iterating through shapes";
#endif
		tested_time = s->intersected_at( ray );
		if( tested_time ) {
			if ( closest_intersected_time ) {
				if ( *tested_time < *closest_intersected_time ) {
					// found one closer
					closest_intersected_time = tested_time;
					shape = s;
				}
			} else {
				// First intersection we come acrost
				closest_intersected_time = tested_time;
				shape = s;
			}
		}
	}
	return shape;

}


boost::optional<const Shape*> SimpleEnvironment::closest_intersection( const Ray& ray ) const {
	return closest_intersection_internal( ray, this->shapes );
}

void SimpleEnvironment::create_image_interal(Image_2D* img, const std::vector<Shape*>& shapes, ScreenIterator start, ScreenIterator end, const LightSource& light, boost::progress_display* prog ) {
	boost::optional<const Shape*> intersected_shape;

	while( start != end ) {

		intersected_shape = closest_intersection_internal(*start, shapes);

		if( intersected_shape ) {
			// TODO repeat call to intersected at
			img->set(start.get_x(), start.get_y(), (*intersected_shape)->illuminate(light, *start, *((*intersected_shape)->intersected_at(*start)) ));
		}

		++start;
#ifdef PROGRESS
		if(prog != NULL) {
			++(*prog);
		}
#endif
	}


}


Image_2D SimpleEnvironment::create_image() const {
	// General setup
	Image_2D img(this->screen.blank_image());
	// TODO cache screen?
	ScreenIterator start = this->screen.begin();
	ScreenIterator end = this->screen.end();

	int total_work = img.x_size() * img.y_size();

#ifdef PROGRESS
	// boost progress
	boost::progress_display prog( total_work );
#endif

#ifdef THREADS
	boost::thread_group workers;

	// start a bunch of threads
	for( unsigned int i = 0; i < NUM_THREADS; ++i ) {
		unsigned int part = (total_work*i+total_work)/NUM_THREADS - (total_work*i)/NUM_THREADS;
		end = start + part;
		workers.create_thread(SimpleWorker(&img, this->light, start, end, this->shapes));
		start = end;
	}

	// join with all threads
	workers.join_all();
#else
	create_image_interal(&img, this->shapes, start, end, this->light, &prog);
#endif

	return img;
}

#ifdef LOGGING
std::string SimpleEnvironment::to_string() {
	std::string info = "";
	info += nested_start;
	{
		info += "primitives: " + boost::lexical_cast<std::string>(this->number_of_primitives) + list_sep;
		info += "screen: " + this->screen.to_string() + list_sep;
		info += "ambient_light_intensity: " + boost::lexical_cast<std::string>(this->light.ambient_intensity) + list_sep;
		info += "light_source_intensity: " + boost::lexical_cast<std::string>(this->light.light_source_intensity) + list_sep;
		info += std::string("light_source_location: ") + this->light.light_source_location.to_string() + list_sep;
		info += std::string("shapes: ") + nested_start;
		for( const Shape* const shape : this->shapes ) {
			info += "shape: " + shape->to_string() + list_sep;
		}
		info += nested_finish;
	}
	info += nested_finish;
	return info;
}

void SimpleEnvironment::log_state() {
	LOG(INFO) << "SimpleEnv: " + this->to_string();
}
#endif
