/*
 * common.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __common_h__
#define __common_h__

#ifndef LOGGING
#include <iostream>
#endif

#ifdef LOGGING
#include <glog/logging.h>
#endif 

void init_log() {
#ifdef LOGGING
	google::InitGoogleLogging("RayTracer");
	FLAGS_minloglevel = 0;
	FLAGS_logtostderr = 1;
	LOG(INFO) << "Logging enabled";
#endif 
}

void init_debug() {
#ifdef DEBUG
#ifdef LOGGING
	LOG(INFO) << "Debugging on";
#endif
#ifndef LOGGING
	std::cout << "DEBUG ON" << std::endl;
#endif
#endif
}

void init() {
	init_log();
	init_debug();
}

#endif /* !__common_h__ */

