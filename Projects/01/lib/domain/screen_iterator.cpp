/*
 * screen_iterator.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/screen_iterator.h"
#include "raytracer/domain/screen.h"

#ifdef LOGGING
#include <glog/logging.h>
#endif

ScreenIterator::ScreenIterator(const Screen* screen, int current_x, int current_y) : 
	parent(screen), current_x( current_x ), current_y( current_y ), current(NULL) { 
#ifdef LOGGING
		LOG(INFO) << "Using regular constructor for Screen Iterator";
#endif
		populate_ray();
	}

ScreenIterator::ScreenIterator(const ScreenIterator& other) :
	current_x(other.current_x), current_y(other.current_y), parent(other.parent), current(NULL) {
#ifdef LOGGING
		LOG(INFO) << "Using copy constructor for Screen Iterator";
#endif
		this->current = new Ray(*(other.current));
	}

void ScreenIterator::destroy_ray() {
	if( this->current != NULL ) {
#ifdef LOGGING
	LOG(INFO) << "Deleteing ray";
#endif
		delete this->current;
		this->current = NULL;
	}
}

ScreenIterator::~ScreenIterator() {
	this->destroy_ray();
}

void ScreenIterator::populate_ray() {
#ifdef LOGGING
	LOG(INFO) << "populating ray";
#endif
	this->destroy_ray();
	const Vector_3D& start = this->parent->viewpoint;
	Vector_3D direction = this->parent->lower_left_corner + 
		(0.5 + this->current_x) / this->parent->resolution_x * this->parent->horizontal + 
		(0.5 + this->current_y) / this->parent->resolution_y * this->parent->vertical;
	this->current = new Ray(start, direction);
}

ScreenIterator& ScreenIterator::operator=(const ScreenIterator& other ) {
	if( this == &other ) {
		return *this;
	}
#ifdef LOGGING
	LOG(INFO) << "using assignment operator for Screen iterator";
#endif
	this->parent = other.parent;
	this->current_x = other.current_x;
	this->current_y = other.current_y;
	this->destroy_ray();
	this->current = new Ray(*(other.current));
	return *this;
}

ScreenIterator& ScreenIterator::operator++() {
#ifdef LOGGING
	LOG(INFO) << "using increment operator for Screen iterator";
#endif
	++(this->current_x);
	if( this->current_x >= this->parent->resolution_x ) {
		this->current_x = 0;
		++(this->current_y);
	}
	this->destroy_ray();
	this->populate_ray();
	return *this;
}

ScreenIterator ScreenIterator::operator++(int) {
	ScreenIterator other(*this);
	operator++();
	return other;
}

bool ScreenIterator::operator==(const ScreenIterator& other) const {
	return 
		this->current_x == other.current_x && 
		this->current_y == other.current_y;
}

bool ScreenIterator::operator!=(const ScreenIterator& other) const {
	return !(this->operator==(other));
}

const Ray& ScreenIterator::operator*() const {
#ifdef LOGGING
	LOG(INFO) << "Dereference";
#endif
	return *(this->current);
}

const Ray* ScreenIterator::operator->() const {
	return (this->current);
}

