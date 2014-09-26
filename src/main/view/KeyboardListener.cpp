/* 
 * File:   KeyboardListener.cpp
 * Author: williampoynter
 * 
 * Created on October 13, 2013, 9:55 AM
 */

#include "KeyboardListener.h"
#include "../util/Logger.h"
#include <sstream>

namespace gs {

KeyboardListener::KeyboardListener(IEventManagerPtr _eventManager) : eventManager(_eventManager) {
	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		previousState[i] = false;
	}
}

KeyboardListener::~KeyboardListener() {
}

void KeyboardListener::update() {
	switch (gameState) {
		case IN_GAME:
			inGameUpdate();
			break;
		case PAUSED:
			pausedUpdate();
			break;
		case LOADING:
			loadingUpdate();
			break;
		case MENU:
			menuUpdate();
			break;
	}
	
}

void KeyboardListener::inGameUpdate() {
	bool resetDirection = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) != previousState[sf::Keyboard::Right]) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			ChangePlayerDirectionEvent changePlayerDirectionEvent(RIGHT);
			eventManager->fireEvent(changePlayerDirectionEvent);
		} else {
			resetDirection = true;
		}
		previousState[sf::Keyboard::Right] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) != previousState[sf::Keyboard::Down]) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			ChangePlayerDirectionEvent changePlayerDirectionEvent(DOWN);
			eventManager->fireEvent(changePlayerDirectionEvent);
		} else {
			resetDirection = true;
		}
		previousState[sf::Keyboard::Down] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) != previousState[sf::Keyboard::Left]) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			ChangePlayerDirectionEvent changePlayerDirectionEvent(LEFT);
			eventManager->fireEvent(changePlayerDirectionEvent);
		} else {
			resetDirection = true;
		}
		previousState[sf::Keyboard::Left] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) != previousState[sf::Keyboard::P])  {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			GameStateChangedEvent gameStateChangedEvent(PAUSED);
			eventManager->fireEvent(gameStateChangedEvent);
		} else {
			resetDirection = true;
		}
		previousState[sf::Keyboard::P] = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
	}

	if (resetDirection) {
		ChangePlayerDirectionEvent changePlayerDirectionEvent(NONE);
		eventManager->fireEvent(changePlayerDirectionEvent);
	}
}

void KeyboardListener::pausedUpdate() {
	bool resetDirection = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) != previousState[sf::Keyboard::P])  {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			GameStateChangedEvent gameStateChangedEvent(IN_GAME);
			eventManager->fireEvent(gameStateChangedEvent);
		} else {
			resetDirection = true;
		}
		previousState[sf::Keyboard::P] = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) != previousState[sf::Keyboard::Escape])  {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			GameEndEvent gameEndEvent;
			eventManager->fireEvent(gameEndEvent);
		} else {
			resetDirection = true;
		}
		previousState[sf::Keyboard::Escape] = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	}

	if (resetDirection) {
		//MoveMenuPointerEvent moveMenuPointerEvent(NONE);
		//eventManager->fireEvent(moveMenuPointerEvent);
	}
}

void KeyboardListener::loadingUpdate() {
	//Do nothing! We're Loading
}

void KeyboardListener::menuUpdate() {
	bool resetDirection = false;
	//We're in a menu update
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) != previousState[sf::Keyboard::Down]) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			//MoveMenuPointerEvent moveMenuPointerEvent(DOWN);
			//eventManager->fireEvent(moveMenuPointerEvent);
			MenuActionEvent menuActionEvent(MenuActionEvent::Action::DOWN);
			eventManager->fireEvent(menuActionEvent);
		} else {
			resetDirection = true;
		}
		previousState[sf::Keyboard::Down] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) != previousState[sf::Keyboard::Up]) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			//MoveMenuPointerEvent moveMenuPointerEvent(UP);
			//eventManager->fireEvent(moveMenuPointerEvent);
			MenuActionEvent menuActionEvent(MenuActionEvent::Action::UP);
			eventManager->fireEvent(menuActionEvent);
		} else {
			resetDirection = true;
		}
		previousState[sf::Keyboard::Up] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) != previousState[sf::Keyboard::Return]) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			//MenuSelectEvent menuSelectEvent;
			//eventManager->fireEvent(menuSelectEvent);
			MenuActionEvent menuActionEvent(MenuActionEvent::Action::SELECT);
			eventManager->fireEvent(menuActionEvent);
		} else {
			resetDirection = true;
		}
		previousState[sf::Keyboard::Return] = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
	}

	if (resetDirection) {
		//MoveMenuPointerEvent moveMenuPointerEvent(NONE);
		//eventManager->fireEvent(moveMenuPointerEvent);
	}
}

void KeyboardListener::onEvent(Event& event) {
	
	switch (event.getType()) {
		case GAME_STATE_CHANGED_EVENT:
			onGameStateChanged((GameStateChangedEvent&) event);
			break;
		default:
			const short eventType = event.getType();
			std::stringstream ss;
			ss << "Un-Handled: " << eventType;
		    ERR << ss.str() << std::endl;
			break;
	}
}

void KeyboardListener::onGameStateChanged(GameStateChangedEvent& event) {
	gameState = event.getState();
}

}