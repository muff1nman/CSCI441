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
	Image_2D img(this->config.screen.blank_image());
	// TODO cache screen?
	ScreenIterator i = this->config.screen.begin();
	ScreenIterator end =  this->config.screen.end();
	boost::optional<const Shape*> intersected_shape;
	while( i != end ) {
		intersected_shape = this->closest_intersection( *i );
		if( intersected_shape ) {
			img.set(i.get_x(), i.get_y(), (*intersected_shape)->illuminate(this->config.light_source_location, this->config.light_source_intensity, i->direction() ));
		}
		++i;
	}
	return img;
}

#ifdef LOGGING
std::string SimpleEnvironment::to_string() {
	std::string info = "";
	info += nested_start;
	{
		info += "config: " + this->config.to_string() + sep;
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
