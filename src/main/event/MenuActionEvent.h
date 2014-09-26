/* 
 * File:   MenuActionEvent.h
 * Author: williampoynter
 *
 * Created on September 26, 2014, 11:51 AM
 */

#ifndef MENUACTIONEVENT_H
#define	MENUACTIONEVENT_H

#include "Event.hpp"

namespace gs {

class MenuActionEvent : public Event {
public:
	MenuActionEvent(Action _action) : action(_action) {};

	virtual EventEnum getType() const {
		return MENU_ACTION_EVENT;
	}

	Direction getAction() const {
		return action;
	}
	
	static enum Action {UP, DOWN, SELECT};

private:
	Action action;
};

}

#endif	/* MENUACTIONEVENT_H */

