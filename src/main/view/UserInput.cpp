/* 
 * File:   UserInput.cpp
 * Author: williampoynter
 * 
 * Created on October 13, 2013, 9:26 AM
 */

#include "UserInput.h"
#include "../event/GameStateChangedEvent.h"
#include "../util/Logger.h"

using namespace gs;

UserInput::UserInput(
	IEventManagerPtr _eventManager, 
	IKeyboardListenerShrPtr _keyboard) : eventManager(_eventManager), keyboard(_keyboard) {
	
	eventManager->addListener(GAME_STATE_CHANGED_EVENT, MAKE_EVENT_LISTENER(keyboard));
}

UserInput::~UserInput() {
	DBG << "Destroyed" << std::endl;
}

void UserInput::update() {
	keyboard->update();
}
