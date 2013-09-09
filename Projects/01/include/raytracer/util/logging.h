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
// TODO ensure that all derived classes dont have this following include
#include <glog/logging.h>
#endif

class Logging {

#ifdef LOGGING
	public:
		//std::string to_string() { return "instance of " + std::string(typeid(this).name()); }
		virtual std::string to_string() const { return "Unknown"; }
#endif
		virtual ~Logging() { }

};

#endif /* !__logging_h__ */

