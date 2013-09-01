/*
 * screen_iterator.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/screen_iterator.h"
#include "raytracer/domain/screen.h"


ScreenIterator& ScreenIterator::operator=(const ScreenIterator& other ) {
	if( this == &other ) {
		return *this;
	}
	this->parent = other.parent;
	this->current_x = other.current_x;
	this->current_y = other.current_y;
	return *this;
}

ScreenIterator& ScreenIterator::operator++() {
	++(this->current_x);
	if( this->current_x >= this->parent->resolution_x ) {
		this->current_x = 0;
		++(this->current_y);
	}
	return *this;
}

ScreenIterator ScreenIterator::operator++(int) {
	ScreenIterator other(*this);
	operator++();
	return other;
}

bool ScreenIterator::operator==(const ScreenIterator& other) {
	return 
		this->current_x == other.current_x && 
		this->current_y == other.current_y;
}

bool ScreenIterator::operator!=(const ScreenIterator& other) {
	return !(this->operator==(other));
}

Ray ScreenIterator::operator*() {
	const Vector_3D& start = this->parent->viewpoint;
	Vector_3D direction = this->parent->lower_left_corner + 
		(0.5 + this->current_x) / this->parent->resolution_x * this->parent->horizontal + 
		(0.5 + this->current_y) / this->parent->resolution_y * this->parent->vertical;
	return Ray(start, direction);
}


