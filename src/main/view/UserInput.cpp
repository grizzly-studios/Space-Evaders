/* 
 * File:   UserInput.cpp
 * Author: williampoynter
 * 
 * Created on October 13, 2013, 9:26 AM
 */

#include "UserInput.h"

using namespace gs;

UserInput::UserInput(IEventManagerPtr _eventManager) : eventManager(_eventManager) {
	
}

UserInput::~UserInput() {
	std::cout << __FILE__ << " destroyed" << std::endl;
}

void UserInput::update() {
	
}