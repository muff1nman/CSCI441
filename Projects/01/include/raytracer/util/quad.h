/*
 * quad.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __quad_h__
#define __quad_h__

#include <vector>
#include <cmath>

/**
 * Returns the discriminate of the given quadratic formula given in the form of:
 *
 * 0 = Ax^2 + Bx + C
 */
double discriminate( double A, double B, double C ) {
	return std::pow(B,2) - 4.0 * A * C;
}

/**
 * Returns the solutions to the given quadratic formual given in the form of:
 *
 * 0 = Ax^2 + Bx + C
 *
 * The vector will be empty when the discrimiate is less than zero
 *
 * The vector will hold one solution when the discrimiate is zero
 *
 * The vector will hold two solutions when the discrimate is greater than zero
 */
std::vector<double> quadratic_roots( double A, double B, double C ) {
	std::vector<double> roots(2);
	double dis = discriminate( A, B, C );
	if ( dis < 0.0 ) {
		// noop
	} else if ( dis > 0.0 ) {
		roots.push_back( ( -B - sqrt( dis ) ) / ( 2.0 * A ));
		roots.push_back( ( -B + sqrt( dis ) ) / ( 2.0 * A ));
	} else {
		roots.push_back( -B / (2.0 * A) );
	}

	return roots;
}

#endif /* !__quad_h__ */

