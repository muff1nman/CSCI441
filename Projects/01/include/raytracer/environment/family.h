/*
 * family.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __family_h__
#define __family_h__

class SimpleEnvironment;

class Family {
	public:

		Family( const SimpleEnvironment* house ) : house(house) { }

		bool other_shape_is_me( const Family* other ) const {
			return this == other;
		}

	protected:
		const SimpleEnvironment* house;
};

#endif /* !__family_h__ */

