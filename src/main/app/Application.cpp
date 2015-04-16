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

	size_t pos;

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
			pos = resolutionString.find_first_of("x");
			WIDTH = atoi(resolutionString.substr(0,pos).c_str());
			HEIGHT = atoi(resolutionString.substr(pos+1).c_str());
			i++;
		} else if (arg.substr(0, pos = arg.find("=")) == "-v"){
			if (pos == std::string::npos) {
				LogHandler::getInstance()->debugLog.setOutput(CONSOLE);
				LogHandler::getInstance()->infoLog.setOutput(CONSOLE);
				LogHandler::getInstance()->warningLog.setOutput(CONSOLE);
				LogHandler::getInstance()->errorLog.setOutput(CONSOLE);
			} else {
				std::string extraArgs = arg.substr(pos + 1);
				for (char& c : extraArgs) {
					if (c == 'd') {
						LogHandler::getInstance()->debugLog.setOutput(CONSOLE);
					}
					if (c == 'i') {
						LogHandler::getInstance()->infoLog.setOutput(CONSOLE);
					}
					if (c == 'w') {
						LogHandler::getInstance()->warningLog.setOutput(CONSOLE);
					}
					if (c == 'e') {
						LogHandler::getInstance()->errorLog.setOutput(CONSOLE);
					}
				}
			}
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
	INFO << "Beginning init" << std::endl;
	clock = new sf::Clock();
	eventManager = IEventManagerPtr(new EventManager);

	/* Create window */
	settings.antialiasingLevel = AL;
	window = RenderWindowShPtr(new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Space Evaders",
		sf::Style::Close, settings));
	window->setVerticalSyncEnabled(true);
	sf::View renderView(sf::FloatRect(0, 0, GBL::WIDTH, GBL::HEIGHT));
	window->setView(renderView);

	/* Create everything core to game */
	logic = ILogicPtr(new Logic(eventManager));
	IKeyboardListenerShrPtr keyboard(new KeyboardListener(eventManager));
	IUserInputShPtr userInput(new UserInput(eventManager,keyboard));
	ISpriteFactoryShPtr spriteFactory(new SpriteFactory());
	view = IViewPtr(new View(eventManager, window, userInput, spriteFactory));

	/* Create everything for view */
	IStyleManagerShPtr styleManager(new StyleManager());
	styleManager->setFont("assets/arial.ttf");
	IMenuScreenShPtr menuScreen(new MenuScreen(styleManager));
	IPausedScreenShPtr pausedScreen(new PausedScreen(styleManager));
	ILoadingScreenShPtr loadingScreen(new LoadingScreen(styleManager));
	IIntroScreenShPtr introScreen(new IntroScreen(styleManager, eventManager));
	IGameOverScreenShPtr gameOverScreen(new GameOverScreen(styleManager, eventManager));
	ICreditsScreenShPtr creditsScreen(new CreditsScreen(styleManager));

	/* Menu Screens */
	view->addScreen(menuScreen);
	view->addScreen(creditsScreen);

	/* In Game Screens */
	view->addScreen(pausedScreen);
	view->addScreen(gameOverScreen);
	
	/* Other Screens */
	view->addScreen(loadingScreen);
	view->addScreen(introScreen);

	/* Now everything view needs has been created we can initialise it */
	view->init();

	/* Setup the event listeners */
	eventManager->addListener(ENTITY_MOVED_EVENT, MAKE_EVENT_LISTENER(view));
	eventManager->addListener(ENTITY_CREATED_EVENT, MAKE_EVENT_LISTENER(view));
	eventManager->addListener(ENTITY_DELETED_EVENT, MAKE_EVENT_LISTENER(view));
	eventManager->addListener(CHANGE_PLAYER_DIRECTION_EVENT, MAKE_EVENT_LISTENER(logic));
	eventManager->addListener(GAME_STATE_CHANGED_EVENT, MAKE_EVENT_LISTENER(logic));
	eventManager->addListener(GAME_STATE_CHANGED_EVENT, MAKE_EVENT_LISTENER(view));
	eventManager->addListener(GAME_START_EVENT, MAKE_EVENT_LISTENER(logic));
	eventManager->addListener(GAME_END_EVENT, MAKE_EVENT_LISTENER(logic));
	eventManager->addListener(GAME_END_EVENT, MAKE_EVENT_LISTENER(view));
	eventManager->addListener(MENU_ACTION_EVENT, MAKE_EVENT_LISTENER(view));

	INFO << "Ending init" << std::endl;
	
	/* Now we're done loading. Show the intro */
	GameStateChangedEvent gameStateChangedEvent(INTRO);
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
		sf::Time elapsed = clock->restart();
		view->update(elapsed.asMicroseconds());
		logic->update(elapsed.asMicroseconds());
		view->render();
	}
}
