/*
 * util.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __util_h__
#define __util_h__

static unsigned char clampnround( double x ) {
	if (x>255)
		x = 255;
	if (x<0) 
		x = 0;
	return (unsigned char)floor(x+.5);
}

#endif /* !__util_h__ */

