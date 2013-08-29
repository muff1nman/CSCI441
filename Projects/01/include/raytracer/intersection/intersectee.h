/*
 * intersectee.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __intersectee_h__
#define __intersectee_h__

/**
 * An abstract class for adding the capability for a shape to know if it is
 * intersected.
 */
class Intersectee {

	virtual bool is_intersected( Ray r ) const;

	virtual double intersected_at( Ray r ) const;

};
#endif /* !__intersectee_h__ */

