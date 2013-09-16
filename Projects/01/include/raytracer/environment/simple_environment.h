/*
 * simple_environment.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __simple_environment_h__
#define __simple_environment_h__

#include "raytracer/environment/environment.h"
#include "raytracer/config/config.h"
#include "raytracer/domain/shapes/shape.h"
#include "raytracer/environment/screen.h"
#include "raytracer/environment/light_source.h"

#ifdef LOGGING
#include <glog/logging.h>
#include <string>
#include <boost/lexical_cast.hpp>
#endif

#include <vector>
#include <boost/optional.hpp>
#include <boost/function.hpp>

class SimpleEnvironment : public Environment {
	public:
		SimpleEnvironment(
			const Screen& screen,
			const LightSource& light,
			int number_of_primitives) : 
		screen( screen ),
		light( light ),
		number_of_primitives( number_of_primitives ) { }

		~SimpleEnvironment();

		void add_shape(Shape* shape);

		struct default_time_compare {
			float operator()(double time_1, double time_2) const {
				return time_1 < time_2;
			}
		};

		/**
		 * Returns a pointer to the closest shape that is intersected by the given ray
		 *
		 * There may be no intersected shape in which case the return value is false
		 *
		 */
		boost::optional<const Shape*> closest_intersection( const Ray& ray, boost::function<float (double t1, double t2)> time_compare = default_time_compare() ) const;

		//boost::optional<const Shape*> closest_intersection_within_time( const Ray& ray ) const;

		/**
		 * Creates a populated image
		 */
		Image_2D create_image() const;


#ifdef LOGGING
		void log_state();
#endif

	private:
		Screen screen;
		LightSource light;
		int number_of_primitives;
		std::vector<Shape*> shapes;

#ifdef LOGGING
		std::string to_string();
#endif

};

#endif /* !__simple_environment_h__ */

