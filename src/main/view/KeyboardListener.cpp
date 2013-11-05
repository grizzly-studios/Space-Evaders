/* 
 * File:   KeyboardListener.cpp
 * Author: williampoynter
 * 
 * Created on October 13, 2013, 9:55 AM
 */

#include "KeyboardListener.h"

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
	
	if (resetDirection) {
		ChangePlayerDirectionEvent changePlayerDirectionEvent(NONE);
			eventManager->fireEvent(changePlayerDirectionEvent);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		GameStateChangedEvent gameStateChangedEvent(PAUSED);
		eventManager->fireEvent(gameStateChangedEvent);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		GameStateChangedEvent gameStateChangedEvent(MENU);
		eventManager->fireEvent(gameStateChangedEvent);
	}
}

void KeyboardListener::pausedUpdate() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		GameStateChangedEvent gameStateChangedEvent(IN_GAME);
		eventManager->fireEvent(gameStateChangedEvent);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		GameStateChangedEvent gameStateChangedEvent(MENU);
		eventManager->fireEvent(gameStateChangedEvent);
	}
}

void KeyboardListener::loadingUpdate() {
	
}

void KeyboardListener::menuUpdate() {
	
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