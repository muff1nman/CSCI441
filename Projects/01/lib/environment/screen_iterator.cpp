/*
 * screen_iterator.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/environment/screen_iterator.h"
#include "raytracer/environment/screen.h"

ScreenIterator::ScreenIterator(const Screen* screen, int current_x, int current_y) : 
	parent(screen), current_x( current_x ), current_y( current_y ), current(NULL) { 
		populate_ray();
	}

ScreenIterator::ScreenIterator(const ScreenIterator& other) :
	parent(other.parent), current_x(other.current_x), current_y(other.current_y), current(NULL) {
		this->current = new Ray(*(other.current));
	}

void ScreenIterator::destroy_ray() {
	if( this->current != NULL ) {
		delete this->current;
		this->current = NULL;
	}
}

ScreenIterator::~ScreenIterator() {
	this->destroy_ray();
}

void ScreenIterator::populate_ray() {
	this->destroy_ray();
	this->current_point = this->parent->upper_left_corner + 
		(0.5 + this->current_x) / this->parent->resolution_x * this->parent->horizontal + 
		(0.5 + this->current_y) / this->parent->resolution_y * -1 * this->parent->vertical;
	this->current = new Ray(this->parent->viewpoint, this->current_point);
}

ScreenIterator& ScreenIterator::operator=(const ScreenIterator& other ) {
	if( this == &other ) {
		return *this;
	}
	this->parent = other.parent;
	this->current_x = other.current_x;
	this->current_y = other.current_y;
	this->destroy_ray();
	this->current = new Ray(*(other.current));
	return *this;
}

ScreenIterator& ScreenIterator::operator++() {
	++(this->current_x);
	if( this->current_x >= this->parent->resolution_x ) {
		this->current_x = 0;
		++(this->current_y);
	}
	this->destroy_ray();
	this->populate_ray();
	return *this;
}

ScreenIterator ScreenIterator::operator+(int num) {
	ScreenIterator other(*this);
	while( num > 0 ) {
		++other;
		--num;
	}
	return other;
}

ScreenIterator ScreenIterator::operator++(int) {
	ScreenIterator other(*this);
	operator++();
	return other;
}

ScreenIterator& ScreenIterator::operator--() {
	--(this->current_x);
	if( this->current_x < 0 ) {
		this->current_x = this->parent->resolution_x - 1;
		--(this->current_y);
	}
	this->destroy_ray();
	this->populate_ray();
	return *this;
}

ScreenIterator ScreenIterator::operator--(int) {
	ScreenIterator other(*this);
	operator--();
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
	return *(this->current);
}

const Ray* ScreenIterator::operator->() const {
	return (this->current);
}

#ifdef LOGGING
std::string ScreenIterator::to_string() const { 
	std::string info = std::string("ray at: (") + boost::lexical_cast<std::string>(current_x) + ", " + boost::lexical_cast<std::string>(current_y) + ")";
	info += " or " + this->current_point.to_string();
	return info;
}
#endif
