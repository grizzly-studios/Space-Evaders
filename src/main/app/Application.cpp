/* 
 * File:   Application.cpp
 * Author: williampoynter
 * 
 * Created on September 25, 2013, 1:11 AM
 */

#include "Application.h"
#include "../util/Logger.h"

using namespace gs;

Application::Application(int argc, char** argv) {
	flush = false;

	FR = 50;
	AL = 4;
	WIDTH = 480; HEIGHT = 704;

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
			CHANGE_LOG(false, true, FULL);
		} else if(arg == "-vf"){
			CHANGE_LOG(true, true, FULL);
		}else{
			WARN("Unknown Flag: " + arg);
		}
	}
	//No point in INFO, WARN or DEBUG messages before this point
	INFO("Application successfully created");
}

void Application::init() { 
	INFO("Begining init");
	eventManager = IEventManagerPtr(new EventManager);
	
	settings.antialiasingLevel = AL;

	window = RenderWindowShPtr(new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Space Evaders",
		sf::Style::Close, settings));
	window->setVerticalSyncEnabled(true);

	logic = ILogicPtr(new Logic(eventManager));
	
	IKeyboardListenerShrPtr keyboard(new KeyboardListener(eventManager));
	IUserInputShPtr userInput(new UserInput(eventManager,keyboard));
	ISpriteFactoryShPtr spriteFactory(new SpriteFactory());
	view = IViewPtr(new View(eventManager, window, userInput, spriteFactory));
	view->init();

	eventManager->addListener(ENTITY_MOVED_EVENT, MAKE_EVENT_LISTENER(view));
	eventManager->addListener(ENTITY_CREATED_EVENT, MAKE_EVENT_LISTENER(view));
	eventManager->addListener(CHANGE_PLAYER_DIRECTION_EVENT, MAKE_EVENT_LISTENER(logic));

	INFO("Ending init");
	
	//Set initial GameState
	GameStateChangedEvent gameStateChangedEvent(IN_GAME);
	eventManager->fireEvent(gameStateChangedEvent);
}

Application::~Application() {
	DBG("Destroyed");
}

void Application::load() {
	logic->generateLevel();
}

void Application::run() {
	
	load();
	
	INFO("Beginning while loop");
	while(window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window->close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					INFO("Request to close window registered - closing window");
					window->close();
				}
			}
		}

		view->update();
		logic->update();
		view->render();
	}
}
