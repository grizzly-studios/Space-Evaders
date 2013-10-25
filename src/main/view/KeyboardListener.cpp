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
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		//KeyBoardRightEvent right;
		//eventManager->fireEvent(right);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		//KeyBoardDownEvent down;
		//eventManager->fireEvent(down);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		//KeyBoardLeftEvent left;
		//eventManager->fireEvent(left);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		//KeyBoardUpEvent up;
		//eventManager->fireEvent(up);
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

}