/*
 * vector_3D.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "raytracer/domain/vector_3D.h"
#include <cmath>

Vector_3D Vector_3D::normal() const {
	double magnitude = std::sqrt(std::pow(this->x,2) + std::pow(this->y,2) + std::pow(this->z,2));
	return Vector_3D(
			this->x / magnitude,
			this->y / magnitude,
			this->z / magnitude);
}

Vector_3D Vector_3D::operator+( const Vector_3D& other ) const {
	return Vector_3D(
			this->x + other.get_x(),
			this->y + other.get_y(),
			this->z + other.get_z());
}

Vector_3D Vector_3D::operator-( const Vector_3D& other ) const {
	return Vector_3D(
			this->x - other.get_x(),
			this->y - other.get_y(),
			this->z - other.get_z());

}

double Vector_3D::operator*( const Vector_3D& other ) const {
	return
			this->x * other.x +
			this->y * other.y +
			this->z * other.z;
}

Vector_3D Vector_3D::operator*( double scalar ) const {
	return Vector_3D(
			this->x * scalar,
			this->y * scalar,
			this->z * scalar);
}

Vector_3D operator*( double scalar, const Vector_3D& other ) {
	return other * scalar;
}

#ifdef DEBUG
std::string Vector_3D::to_string() const {
	std::string info = "";
	info += nested_start;
	{
		info += "x: " + boost::lexical_cast<std::string>(x) + list_sep;
		info += "y: " + boost::lexical_cast<std::string>(y) + list_sep;
		info += "z: " + boost::lexical_cast<std::string>(z) + sep;
	}
	info += nested_finish;
	return info;
}
#endif


