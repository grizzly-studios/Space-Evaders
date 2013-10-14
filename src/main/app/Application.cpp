/* 
 * File:   Application.cpp
 * Author: williampoynter
 * 
 * Created on September 25, 2013, 1:11 AM
 */

#include <SFML/Graphics/RenderWindow.hpp>

#include "Application.h"
#include "../event/EventManager.hpp"
#include "../logic/Logic.hpp"
#include "../view/View.hpp"

namespace gs {

	Application::Application(int argc, char** argv) {
			
			flush = false;
			loge = logger::getInstance();
			
			loge->log("Creating Application", INFO);
			
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
					} else{
							loge->log("Unknown Flag: " + arg, ERROR);
					}
			}
			loge->log("Application successfully created", INFO);
	}

	void Application::init() { 
		loge->log("Begining init", INFO);

		eventManager = IEventManagerPtr(new EventManager);

		logic = ILogicPtr(new Logic(eventManager));
		view = IViewPtr(new View(eventManager));

		settings.antialiasingLevel = AL;

		window = new sf::RenderWindow(sf::VideoMode(WIDTH,HEIGHT),"Space Evaders",sf::Style::Fullscreen, settings);
		window->setVerticalSyncEnabled(true);

		loge->log("Ending init", INFO);
	}

	Application::~Application() {
		loge->log("Deconstructing application", INFO);
	}

	void Application::run() {
			loge->log("Beginning while loop", INFO);
			while(window->isOpen()) {
					sf::Event event;
					while (window->pollEvent(event)) {
							
						if (event.type == sf::Event::Closed) {
							window->close();
						}
						if (event.type == sf::Event::KeyPressed) {
								if (event.key.code == sf::Keyboard::Escape) {
									loge->log("Request to close window registered - closing window", INFO);
									window->close();
								}
						}
					}
					
					window->clear();
					//window->draw();
					window->display();
			}
	}

}
