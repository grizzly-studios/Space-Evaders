/* 
 * File:   ChangePlayerDirectionEvent.h
 * Author: williampoynter
 *
 * Created on October 26, 2013, 1:56 PM
 */

#ifndef CHANGE_PLAYER_DIRECTION_EVENT_H
#define	CHANGE_PLAYER_DIRECTION_EVENT_H

#include "Event.hpp"
#include "../logic/MobileEntity.h"

namespace gs {

class ChangePlayerDirectionEvent : public Event {
public:
	ChangePlayerDirectionEvent(Direction _direction) : direction(_direction) {}

	virtual EventEnum getType() const {
		return CHANGE_PLAYER_DIRECTION_EVENT;
	}

	Direction getDirection() const {
		return direction;
	}

private:
	Direction direction;
};

}

#endif	/* CHANGE_PLAYER_DIRECTION_EVENT_H */

