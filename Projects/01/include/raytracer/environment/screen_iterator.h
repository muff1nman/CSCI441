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

#include <iterator>

class Screen;

class ScreenIterator: public std::iterator< std::forward_iterator_tag, Ray, int >, public Logging {
	public:
		ScreenIterator(const Screen* screen, int current_x = 0, int current_y = 0);

		ScreenIterator(const ScreenIterator& other);

		~ScreenIterator();

		ScreenIterator& operator=(const ScreenIterator& other );

		ScreenIterator& operator++();

		ScreenIterator operator++(int);

		ScreenIterator& operator--();

		ScreenIterator operator--(int);

		bool operator==(const ScreenIterator& other) const;

		bool operator!=(const ScreenIterator& other) const;

		const Ray& operator*() const;

		const Ray* operator->() const;

		int get_x() const { return current_x; }
		int get_y() const { return current_y; }

#ifdef LOGGING
		std::string to_string() const;
#endif

	private:
		const Screen* parent;

		int current_x;
		int current_y;

		const Ray* current;

		Vector_3D current_point;

		void populate_ray();
		void destroy_ray();

};

#endif /* !__screen_iterator_h__ */

