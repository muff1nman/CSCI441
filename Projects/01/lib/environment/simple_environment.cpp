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


boost::optional<int> SimpleEnvironment::closest_intersection( const Ray& ray ) {
	boost::optional<int> index;
	boost::optional<double> closest_intersected_time;
	boost::optional<double> tested_time;
	int current_index;
	for( const Shape* const s : this->shapes ) {
		tested_time = s->intersected_at( ray );
		if( tested_time ) {
			if ( closest_intersected_time ) {
				if ( *tested_time < *closest_intersected_time ) {
					// found one closer
					closest_intersected_time = tested_time;
					index = current_index;
				}
			} else {
				// First intersection we come acrost
				closest_intersected_time = tested_time;
				index = current_index;
			}
		}
		++current_index;
	}
	return index;
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
