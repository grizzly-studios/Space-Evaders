/* 
 * File:   Application.cpp
 * Author: williampoynter
 * 
 * Created on September 25, 2013, 1:11 AM
 */

#include "Application.h"

using namespace gs;

Application::Application(int argc, char** argv) {
	flush = false;

	FR = 50;
	AL = 4;
	WIDTH = 1024; HEIGHT = 640;

	for (int i = 1; i < argc; i++) {
		std::string arg(argv[i]);
		if (arg == "-f") {
			flush = true;
		} else if (arg == "-fr") {
			FR = atoi(argv[i+1]);
			i++;
		} else if (arg == "-al") {
			AL = atoi(argv[i+1]);
			i++;
		} else if (arg == "-r") {
			std::string resolutionString(argv[i+1]);
			std::size_t pos = resolutionString.find_first_of("x");
			WIDTH = atoi(resolutionString.substr(0,pos).c_str());
			HEIGHT = atoi(resolutionString.substr(pos+1).c_str());
			i++;
		} else if (arg == "-v"){
			changeLog(false, true, DEBUG);
		} else if(arg == "-vf"){
			changeLog(true, true, DEBUG);
		}else{
			log("Unknown Flag: " + arg, ERR, __FILE__, __LINE__);
		}
	}
	//No point in INFO or WARN messages before this point
	log("Application successfully created", INFO, __FILE__, __LINE__);
}

void Application::init() { 
	log("Begining init", INFO, __FILE__, __LINE__);
	eventManager = IEventManagerPtr(new EventManager);
	
	settings.antialiasingLevel = AL;

	window = RenderWindowShPtr(new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Space Evaders",
		sf::Style::Default, settings));
	window->setVerticalSyncEnabled(true);

	logic = ILogicPtr(new Logic(eventManager));
	view = IViewPtr(new View(eventManager, window));
	view->init();

	// TODO: How best to handle this cast?
	eventManager->addListener(ENTITY_MOVED_EVENT,
		std::tr1::dynamic_pointer_cast<IEventListener>(view));
	eventManager->addListener(ENTITY_CREATED_EVENT,
		std::tr1::dynamic_pointer_cast<IEventListener>(view));
	log("Ending init", INFO, __FILE__, __LINE__);
}

Application::~Application() {
	log("Deconstructing application", INFO, __FILE__, __LINE__);
	std::cout << __FILE__ << " destroyed" << std::endl;
}

void Application::run() {
	log("Beginning while loop", INFO, __FILE__, __LINE__);
	while(window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					log("Request to close window registered - closing window", INFO, __FILE__, __LINE__);
					window->close();
				}
			}
		}

		logic->update();
		view->render();
	}
}
