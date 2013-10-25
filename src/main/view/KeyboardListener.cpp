/* 
 * File:   KeyboardListener.cpp
 * Author: williampoynter
 * 
 * Created on October 13, 2013, 9:55 AM
 */

#include <SFML/Window/Keyboard.hpp>

#include "KeyboardListener.h"

namespace gs {

KeyboardListener::KeyboardListener(IEventManagerPtr _eventManager) : eventManager(_eventManager) {
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		MoveEntityEvent moveEntityEvent(RIGHT);
		eventManager->fireEvent(moveEntityEvent);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		MoveEntityEvent moveEntityEvent(DOWN);
		eventManager->fireEvent(moveEntityEvent);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		MoveEntityEvent moveEntityEvent(LEFT);
		eventManager->fireEvent(moveEntityEvent);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		//KeyBoardPEvent p;
		//eventManager->fireEvent(p);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		//KeyBoardEscapeEvent escape;
		//eventManager->fireEvent(escape);
	}
}

void KeyboardListener::onEvent(Event& event) {
	
	switch (event.getType()) {
		case GAME_STATE_CHANGED_EVENT:
			onGameStateChanged((GameStateChangedEvent&) event);
			break;
		default:
			break;
	}
}

void KeyboardListener::onGameStateChanged(GameStateChangedEvent& event) {
	gameState = event.getState();
}

}