/*
 * parse.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __parse_h__
#define __parse_h__

#include "environment.h"

Environment parse( const char* filename );
VectorStream to_vec_stream( const char* filename );

#endif /* !__parse_h__ */

