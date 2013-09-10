/*
 * worker.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __worker_h__
#define __worker_h__

#include <iostream>

class Worker {
	public:
		virtual void operator()() {
			std::cout << "Doing work!" << std::endl;
		}

		virtual ~Worker() { }
};

#endif /* !__worker_h__ */

