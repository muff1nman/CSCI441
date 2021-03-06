/*
 * parser.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __parser_h__
#define __parser_h__

#include <vector>
#include <fstream>
#include <assert.h>

#include "raytracer/config/config.h"
#include "raytracer/environment/simple_environment.h"

SimpleEnvironment* parse( const char* filename );

#endif /* !__parser_h__ */

