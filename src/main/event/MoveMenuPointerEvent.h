/* 
 * File:   MoveMenuPointerEvent.h
 * Author: Rob Parker
 *
 * Created on November 19, 2013, 19:08 PM
 */

#ifndef CHANGE_PLAYER_DIRECTION_EVENT_H
#define	CHANGE_PLAYER_DIRECTION_EVENT_H

#include "Event.hpp"
#include "../logic/MobileEntity.h"

namespace gs {

class MoveMenuPointerEvent : public Event {
public:
	MoveMenuPointerEvent(Direction _direction) : direction(_direction) {}

	virtual EventEnum getType() const {
		return MOVE_MENU_POINTER_EVENT;
	}

	Direction getDirection() const {
		return direction;
	}

private:
	Direction direction;
};

}

#endif	/* CHANGE_PLAYER_DIRECTION_EVENT_H */

