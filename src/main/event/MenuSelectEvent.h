/* 
 * File:   MenuSelectEvent.h
 * Author: Rob Parker
 *
 * Created on November 19, 2013, 19:08 PM
 */

#ifndef MENU_SELECT_EVENT_H
#define	MENU_SELECT_EVENT_H

#include "Event.hpp"

namespace gs {

class MenuSelectEvent : public Event {
public:
	MenuSelectEvent( ) {}

	virtual EventEnum getType() const {
		return MENU_SELECT_EVENT;
	}

private:

};

}

#endif	/* MENU_SELECT_EVENT_H */

