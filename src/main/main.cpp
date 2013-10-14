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

using namespace gs;

/*
 * 
 */
int main(int argc, char** argv) {
	logger *loge = logger::getInstance(); //No point in INFO or WARN messages before this point
	loge->log("Starting application now",INFO);
	Application *app = new Application(argc, argv);
	app->init();
	app->run();

	delete app;

	return 0;
}
