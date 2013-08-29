/*
 * image_output.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __image_output_h__
#define __image_output_h__

#include "raytracer/domain/image_2D.h"
#include <fstream>
#include <cassert>
#include <math.h>

void save_to_ppm_file( const image_2D& image, char* filename );

#endif /* !__image_output_h__ */

