/* 
 * File:   main.cpp
 * Author: WP
 *
 * Created on September 25, 2013, 12:29 AM
 */

#include <cstdlib>

#include <iostream>
#include <tr1/memory>

#include "event/EventManager.hpp"
#include "event/BiscuitEvent.hpp"
#include "event/CheeseEvent.hpp"
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

	// TODO: Find out which cast type we need
	eventManager->addListener(BISCUIT_EVENT, std::tr1::dynamic_pointer_cast<IEventListener>(logic));
	eventManager->addListener(CHEESE_EVENT, std::tr1::dynamic_pointer_cast<IEventListener>(view));

	BiscuitEvent biscuitEvent;
	eventManager->fireEvent(biscuitEvent);

	CheeseEvent cheeseEvent;
	eventManager->fireEvent(cheeseEvent);

	//Application *app = new Application(argc, argv, logic, view);

        // app->init();
        
        // app->run();

	std::cout << "returning..." << std::endl;

    return 0;
}
