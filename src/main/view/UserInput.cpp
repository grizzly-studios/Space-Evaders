/* 
 * File:   UserInput.cpp
 * Author: williampoynter
 * 
 * Created on October 13, 2013, 9:26 AM
 */

#include "UserInput.h"
#include "../event/GameStateChangedEvent.h"

using namespace gs;

UserInput::UserInput(
	IEventManagerPtr _eventManager, 
	IKeyboardListenerShrPtr _keyboard) : eventManager(_eventManager), keyboard(_keyboard) {
	
	eventManager->addListener(GAME_STATE_CHANGED_EVENT,
		std::tr1::dynamic_pointer_cast<IEventListener>(keyboard));
}

UserInput::~UserInput() {
	std::cout << __FILE__ << " destroyed" << std::endl;
}

void UserInput::update() {
	keyboard->update();
}