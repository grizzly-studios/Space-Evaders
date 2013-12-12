/* 
 * File:   main.cpp
 * Author: WP
 *
 * Created on September 25, 2013, 12:29 AM
 */

#include "app/Application.h"
#include "util/Logger.h"

using namespace gs;

/*
 * 
 */
int main(int argc, char** argv) {
	//No point in INFO, WARN or DEBUG messages before this point
	Application *app = new Application(argc, argv); 
	INFO << "Initialising application" << std::endl;
	app->init();
	INFO << "Running application" << std::endl;
	app->run();

	delete app;

	return 0;
}
