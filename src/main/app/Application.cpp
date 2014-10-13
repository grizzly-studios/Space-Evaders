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
	WIDTH = 480; HEIGHT = 640;

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
			LogHandler::getInstance()->debugLog.setOutput(CONSOLE);
			LogHandler::getInstance()->infoLog.setOutput(CONSOLE);
			LogHandler::getInstance()->warningLog.setOutput(CONSOLE);
			LogHandler::getInstance()->errorLog.setOutput(CONSOLE);
		} else if(arg == "-vf"){
			LogHandler::getInstance()->debugLog.setOutput(BOTH);
			LogHandler::getInstance()->infoLog.setOutput(BOTH);
			LogHandler::getInstance()->warningLog.setOutput(BOTH);
			LogHandler::getInstance()->errorLog.setOutput(BOTH);
		}else{
			WARN << "Unknown Flag: " << arg << std::endl;
		}
	}
	//No point in INFO, WARN or DEBUG messages before this point
	INFO << "Application successfully created" << std::endl;
}

void Application::init() { 
	INFO << "Begining init" << std::endl;
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
	
	IStyleManagerShPtr styleManager(new StyleManager());
	styleManager->setFont("assets/arial.ttf");
	IMenuScreenShPtr menuScreen(new MenuScreen(styleManager));
	view->addScreen(menuScreen);

	eventManager->addListener(ENTITY_MOVED_EVENT, MAKE_EVENT_LISTENER(view));
	eventManager->addListener(ENTITY_CREATED_EVENT, MAKE_EVENT_LISTENER(view));
	eventManager->addListener(CHANGE_PLAYER_DIRECTION_EVENT, MAKE_EVENT_LISTENER(logic));
	eventManager->addListener(GAME_STATE_CHANGED_EVENT, MAKE_EVENT_LISTENER(logic));
	eventManager->addListener(GAME_STATE_CHANGED_EVENT, MAKE_EVENT_LISTENER(view));
	//eventManager->addListener(GAME_STATE_CHANGED_EVENT, MAKE_EVENT_LISTENER(keyboard));
	eventManager->addListener(GAME_START_EVENT, MAKE_EVENT_LISTENER(logic));
	eventManager->addListener(GAME_END_EVENT, MAKE_EVENT_LISTENER(logic));
	eventManager->addListener(GAME_END_EVENT, MAKE_EVENT_LISTENER(view));
	eventManager->addListener(MENU_ACTION_EVENT, MAKE_EVENT_LISTENER(view));

	INFO << "Ending init" << std::endl;
	
	//Set initial GameState
	GameStateChangedEvent gameStateChangedEvent(MENU);
	eventManager->fireEvent(gameStateChangedEvent);
}

Application::~Application() {
	DBG << "Destroyed" << std::endl;
}

void Application::load() {
}

void Application::run() {
	
	load();
	
	INFO << "Beginning while loop" << std::endl;
	while(window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}

		view->update();
		logic->update();
		view->render();
	}
}
