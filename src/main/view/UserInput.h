/* 
 * File:   UserInput.h
 * Author: williampoynter
 *
 * Created on October 13, 2013, 9:26 AM
 */

#ifndef USERINPUT_H
#define	USERINPUT_H

#include <iostream>

#include "IUserInput.h"
#include "../event/IEventManager.hpp"

namespace gs {

class UserInput : public IUserInput {
public:
	UserInput(IEventManagerPtr _eventManager);
	virtual ~UserInput();
	
	virtual void update();
private:
	IEventManagerPtr eventManager;
};

}

#endif	/* USERINPUT_H */
