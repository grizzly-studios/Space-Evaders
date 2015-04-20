#include "View.h"

#include <iostream>
#include <string>
#include <sstream>

#include "../util/Logger.h"

using namespace gs;

View::View(IEventManagerPtr _eventManager,
	RenderWindowShPtr _window,
	IUserInputShPtr _userInput)
	: eventManager(_eventManager),
	  window(_window),
	  userInput(_userInput),
	  width(0), height(0) {

	width = window->getSize().x;
	height = window->getSize().y;
}

View::~View() {
	DBG << "Destroyed" << std::endl;
}

void View::init() {
	/* Initially we want to show the loading screen */
	gameState = LOADING; 
	render(); 
	initBackground();
}

void View::update(long int elapsed) {
	userInput->update();
}

void View::addScreen(IScreenShPtr screenPtr) {
	if (screens.find(screenPtr->getType()) != screens.end()) {
		WARN << "Screen " << *screenPtr << 
			" already registered to the View. Overwriting previous instance." << std::endl;
	}
	screens[screenPtr->getType()] = screenPtr;
}

void View::render() {
	//First clear up then make the standards
	window->clear();
	for (RectShapeList::const_iterator it = stars.begin(); it != stars.end(); ++it) {
		window->draw(*it);
	}

	//Now work out what else to draw
	switch (gameState) {
		case IN_GAME:
			screens[GAME_SCREEN]->render(window);
			break;
		case PAUSED:
			screens[PAUSED_SCREEN]->render(window);
			break;
		case LOADING:
			screens[LOADING_SCREEN]->render(window);
			break;
		case MENU:
			switch(MENU_CAST->getSelected()) {
				case MENU_SETTINGS:
					break;
				case MENU_CREDITS:
					screens[CREDITS_SCREEN]->render(window);
					break;
				default:
					screens[MENU_SCREEN]->render(window);
					break;
			}
			break;
		case INTRO:
			screens[INTRO_SCREEN]->render(window);
			break;
		case GAMEOVER:
			screens[GAMEOVER_SCREEN]->render(window);
			break;
		case GAMEWON:
			screens[GAMEWON_SCREEN]->render(window);
			break;
	}
	//Now display
	window->display();
}

void View::onEvent(Event& event) {
	const short eventType = event.getType();
	INFO << "Received event: " << event << std::endl;

	switch (eventType) {
		case GAME_STATE_CHANGED_EVENT: {
			onGameStateChanged((GameStateChangedEvent&) event);
			break;
		}
		case MENU_ACTION_EVENT: {
			MenuActionEvent menuActionEvent = (MenuActionEvent&) event;
			if (menuActionEvent.getAction() == MenuActionEvent::Action::SELECT) {
				selectMenuItem();
			} else if (menuActionEvent.getAction() == MenuActionEvent::Action::BACK) {
				moveMenuBack();
			} else {
				moveMenuPointer(menuActionEvent);
			}
			break;
		}
		default: {
		    ERR << "Un-Handled: " << event << std::endl;
			break;
		}
	}
}

void View::initBackground() {
	// 'Randomly' position some stars
	const int NUM_STARS = 80;
	const int STAR_WIDTH = 3;
	const int SEED = 48;

	std::mt19937 randomNumGen(SEED);
	std::uniform_int_distribution<int> distX(0, GBL::WIDTH);
	std::uniform_int_distribution<int> distY(0, GBL::HEIGHT);
	std::function<int()> genX(std::bind(distX, randomNumGen));
	std::function<int()> genY(std::bind(distY, randomNumGen));
	
	genX();
	
	for (int i=0; i<NUM_STARS; i++) {
		stars.push_back(sf::RectangleShape(sf::Vector2f(STAR_WIDTH, STAR_WIDTH)));
		stars.back().setPosition(genX(), genY());
	}
}

void View::onGameStateChanged(GameStateChangedEvent& event) {
	gameState = event.getState();
}

void View::moveMenuPointer(MenuActionEvent& event){
	switch(event.getAction()){
		case MenuActionEvent::Action::DOWN:
			MENU_CAST->moveMenuPos(-1);
			break;

		case MenuActionEvent::Action::UP:
			MENU_CAST->moveMenuPos(1);
			break;

		case MenuActionEvent::Action::SELECT: //go nowhere. duh!
			break;

		default:
			ERR << "Unable to move menu pointer in direction: " << event.getAction() << std::endl;
			break;
	}
}

void View::moveMenuBack() {
	if (MENU_CAST->getSelected() != MAIN_MENU) {
		MENU_CAST->setSelected(MAIN_MENU);
	}
}

void View::selectMenuItem(){
	//we have been told to activate whatever so go for it!
	switch(MENU_CAST->getMenuPos()){
		case MENU_START:{
			INFO << "Start Game selected" << std::endl;
			//We need to start a new game!
			GameStartEvent gameStartEvent;
			eventManager->fireEvent(gameStartEvent);
			break;
		}
		case MENU_SETTINGS:{
			INFO << "Settings selected" << std::endl;
			MENU_CAST->setSelected(MENU_SETTINGS);
			break;
		}		
		case MENU_CREDITS:{
			//Do nothing for now
			INFO << "Credits selected" << std::endl;
			MENU_CAST->setSelected(MENU_CREDITS);
			break;
		}
		case MENU_QUIT:{
			//Let's quit!
			INFO << "Quit selected" << std::endl;
			window->close();
			break;
		}
		default:{
			ERR << "Unknown menu selection" << MENU_CAST->getMenuPos() << std::endl;
			break;
		}
	}
}
