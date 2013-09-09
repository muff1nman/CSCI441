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

#include <boost/bind.hpp>

SimpleEnvironment::~SimpleEnvironment() {

	// deallocate each shape
	for( int i = 0; i < this->shapes.size(); ++i ) {
		delete this->shapes.at(i);
	}
}

void SimpleEnvironment::add_shape(Shape* shape) {
	this->shapes.push_back( shape );
}

boost::optional<const Shape*> SimpleEnvironment::closest_intersection_within_time( const Ray& ray, double limit ) const {
	return closest_intersection( ray, boost::bind<bool>(time_compare_with_limit(), _1, _2, limit));
}

boost::optional<const Shape*> SimpleEnvironment::closest_intersection( const Ray& ray, boost::function<bool (boost::optional<double> possible_new_value, boost::optional<double> current_min)> time_compare ) const {
	boost::optional<const Shape*> shape;
	boost::optional<double> closest_intersected_time;
	boost::optional<double> tested_time;
	for( int i = 0; i < this->shapes.size(); ++i ) {
		const Shape* const s = this->shapes.at(i);
		// TODO repeat call
		// TODO possible issue if the A term for the ray (Ax + c) is not normalized
		// we may not be able to compare times coming from this value?
		tested_time = s->intersected_at( ray );
		if( time_compare( tested_time, closest_intersected_time )) { 
			closest_intersected_time = tested_time;
			shape = s;
		}
	}
	return shape;

}

Image_2D SimpleEnvironment::create_image() 
#ifndef DEBUG
	const 
#endif
{
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
#ifdef DEBUG
		if( i.get_x() == 88 && i.get_y() == 145 ) {
			std::cout << "Setting pixel debug to: " << i.get_x() << ", " << i.get_y() << std::endl;
			pixel_debug = true;
		} else {
			pixel_debug = false;
		}
#endif

		intersected_shape = this->closest_intersection( *i );

		if( intersected_shape ) {

			// TODO repeat call to intersected at
			double time_intersected_at = *((*intersected_shape)->intersected_at(*i));

			img.set(i.get_x(), i.get_y(), (*intersected_shape)->illuminate(this->light, *i, time_intersected_at ));
#ifdef DEBUG
		if( i.get_x() == 88 && i.get_y() == 145 ) {
			img.set(i.get_x(), i.get_y(), RGB(1.0, 1.0, 0));
		}
#endif
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
