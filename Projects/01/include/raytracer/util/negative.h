/*
 * negative.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __negative_h__
#define __negative_h__

#include <vector>
#include <algorithm>
#include <boost/optional.hpp>

/**
 * Returns the first non-negative result
 *
 * Assumes the list has already been ordered
 *
 */

template <class T>
boost::optional<T> first_nonnegative( std::vector<T> list ) {
	boost::optional<T> the_item;
	for( const T& item : list ) {
		if( item > 0 ) {
			the_item = item;
			break;
		}
	}
	return the_item;
}

#endif /* !__negative_h__ */

