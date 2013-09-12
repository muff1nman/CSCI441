/*
 * common.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __common_h__
#define __common_h__

#ifdef LOGGING
#include <glog/logging.h>
#endif 

#include <iostream>
#include <string>

bool check_params(int argc, char** argv) {
	if( argc < 2 || argc > 3) {
		return false;
	}
	return true;
}

Vector_3D prompt_for_vector() {
	double x,y,z;
	std::cout << "x: ";
	std::cin >> x;
	std::cout << "y: ";
	std::cin >> y;
	std::cout << "z: ";
	std::cin >> z;
	return Vector_3D(x,y,z);
}

std::string input_file_name(int argc, char** argv) {
	if( argc < 2 ) {
#ifdef LOGGING
		LOG(FATAL) << "Please provide an input file as the first parameter";
#endif
	}
	return std::string(argv[1]);
}

std::string output_file_name(int argc, char** argv) {
	std::string file_name(DEFAULT_OUTPUT_FILE);
	if( argc < 3 ) {
#ifdef LOGGING
		LOG(INFO) << "Using default output file name [" << file_name <<  "]";
#endif
	} else {
		file_name = std::string(argv[2]);
#ifdef LOGGING
		LOG(INFO) << "OUTPUT file name is: " << file_name;
#endif
	}
	return file_name;
}

void init_log() {
#ifdef LOGGING
	google::InitGoogleLogging("RayTracer");
	FLAGS_minloglevel = LOG_LEVEL;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
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

