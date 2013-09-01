/*
 * screen_iterator.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __screen_iterator_h__
#define __screen_iterator_h__

#include "raytracer/config/config.h"
#include "raytracer/domain/ray.h"
#include "raytracer/util/logging.h"
class Screen;
class ScreenIterator: public std::iterator< std::forward_iterator_tag, Ray, int >, public Logging {
	public:
		ScreenIterator(const Screen* screen, int current_x = 0, int current_y = 0) : 
			parent(screen), current_x( current_x ), current_y( current_y ) { }

		ScreenIterator(const ScreenIterator& other) : 
			current_x(other.current_x), current_y(other.current_y), parent(other.parent) { }

		ScreenIterator& operator=(const ScreenIterator& other );

		ScreenIterator& operator++();

		ScreenIterator operator++(int);

		bool operator==(const ScreenIterator& other);

		bool operator!=(const ScreenIterator& other);

		Ray operator*();

		//reference operator->();
		
		//friend class Screen;

#ifdef LOGGING
		std::string to_string() { return std::string("ray at: (") + boost::lexical_cast<std::string>(current_x) + ", " + boost::lexical_cast<std::string>(current_y) + ")"; }
#endif

	private:
		int current_x;
		int current_y;
		const Screen* parent;

};

#endif /* !__screen_iterator_h__ */

