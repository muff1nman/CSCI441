/*
 * screen.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __screen_h__
#define __screen_h__

#include "raytracer/config/config.h"
#include "raytracer/domain/vector_3D.h"
#include "raytracer/util/logging.h"
#include "raytracer/domain/screen_iterator.h"
#include "raytracer/domain/image_2D.h"

class Screen : public Logging {

	public:
		Screen( 
				const Vector_3D& viewpoint,
				const Vector_3D& lower_left,
				const Vector_3D& vertical,
				const Vector_3D& horizontal,
				int x,
				int y) :
			viewpoint( viewpoint ),
			lower_left_corner( lower_left ),
			vertical( vertical.normal() ),
			horizontal( horizontal.normal() ),
			resolution_x( x ),
			resolution_y( y ) { }

		Image_2D blank_image() const;

		ScreenIterator begin() const;
		ScreenIterator end() const;

		friend class ScreenIterator;


#ifdef LOGGING
		std::string to_string();
#endif

	private:
		Vector_3D viewpoint;
		Vector_3D lower_left_corner;
		Vector_3D vertical;
		Vector_3D horizontal;

		int resolution_x;
		int resolution_y;
};

#endif /* !__screen_h__ */

