/*
 * logging.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __logging_h__
#define __logging_h__

#include "raytracer/config/config.h"

#ifdef LOGGING
#include <string>
#include <boost/lexical_cast.hpp>
#include <typeinfo>
#endif

class Logging {

#ifdef LOGGING
	public:
		//std::string to_string() { return "instance of " + std::string(typeid(this).name()); }
		virtual std::string to_string() const { return "Unknown"; }
#endif

};

#endif /* !__logging_h__ */

