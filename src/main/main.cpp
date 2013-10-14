/* 
 * File:   main.cpp
 * Author: WP
 *
 * Created on September 25, 2013, 12:29 AM
 */

#include "event/EventManager.hpp"
#include "logic/Logic.hpp"
#include "view/View.hpp"
#include "app/Application.h"

using namespace gs;

/*
 * 
 */
int main(int argc, char** argv) {
	Application *app = new Application(argc, argv);
	app->init();
	app->run();

	delete app;

    return 0;
}
