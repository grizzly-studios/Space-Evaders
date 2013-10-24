/* 
 * File:   main.cpp
 * Author: WP
 *
 * Created on September 25, 2013, 12:29 AM
 */

#include <cstdlib>
#include "event/EventManager.h"
#include "logic/Logic.h"
#include "view/View.h"
#include "app/Application.h"
#include "util/logger.h"

const std::string CLASS = "main";
using namespace gs;

/*
 * 
 */
int main(int argc, char** argv) {
	//No point in INFO, WARN or DEBUG messages before this point
	Application *app = new Application(argc, argv); 
	INFO("Initialising application");
	app->init();
	INFO("Running application");
	app->run();

	delete app;

	return 0;
}
