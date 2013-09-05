/*
 * simple_environment.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/environment/simple_environment.h"

#ifdef PROGRESS
#include <boost/progress.hpp>
#endif

SimpleEnvironment::~SimpleEnvironment() {

	// deallocate each shape
	for( Shape* ptr : this->shapes ) {
		delete ptr;
	}
}

void SimpleEnvironment::add_shape(Shape* shape) {
	this->shapes.push_back( shape );
}


boost::optional<const Shape*> SimpleEnvironment::closest_intersection( const Ray& ray ) const {
	boost::optional<const Shape*> shape;
	boost::optional<double> closest_intersected_time;
	boost::optional<double> tested_time;
	for( const Shape* const s : this->shapes ) {
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


Image_2D SimpleEnvironment::create_image() const {
	// General setup
	Image_2D img(this->screen.blank_image());
	// TODO cache screen?
	ScreenIterator i = this->screen.begin();
	ScreenIterator end =  this->screen.end();
	boost::optional<const Shape*> intersected_shape;

#ifdef PROGRESS
	// boost progress
	boost::progress_display prog( img.x_size() * img.y_size() );
#endif

	while( i != end ) {
		intersected_shape = this->closest_intersection( *i );

		if( intersected_shape ) {
			// TODO repeat call to intersected at
			img.set(i.get_x(), i.get_y(), (*intersected_shape)->illuminate(this->light, *i, *((*intersected_shape)->intersected_at(*i)) ));
		}

		++i;
#ifdef PROGRESS
		++prog;
#endif
	}
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
