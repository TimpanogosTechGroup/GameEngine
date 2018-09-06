#ifndef START_APP_H
#define START_APP_H

#include "Application.h"
class StartApp :
	public Application
{
public:
	StartApp();
	~StartApp();

	void run();
	void initialize();
	void shutdown();
};

#endif