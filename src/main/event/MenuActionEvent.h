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
	enum Action {UP, DOWN, SELECT, BACK};
	
	MenuActionEvent(Action _action) : action(_action) {};

	virtual EventEnum getType() const {
		return MENU_ACTION_EVENT;
	}

	Action getAction() const {
		return action;
	}

private:
	Action action;
};

}

#endif	/* MENUACTIONEVENT_H */

