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

using namespace std;
using namespace gs;

/*
 * 
 */
int main(int argc, char** argv) {
	IEventManagerPtr eventManager(new EventManager);

	ILogicPtr logic(new Logic(eventManager));
	IViewPtr view(new View(eventManager));

	Application *app = new Application(argc, argv, logic, view);
	app->init();
	app->run();

    return 0;
}
