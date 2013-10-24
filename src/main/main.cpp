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
	logger *loge = logger::getInstance(); 
	Application *app = new Application(argc, argv); //No point in INFO or WARN messages before this point
	loge->log("Initialising application", INFO);
	app->init();
	loge->log("Running application", INFO);
	app->run();

	delete app;

	return 0;
}
