/* 
 * File:   MoveEntityEvent.h
 * Author: williampoynter
 *
 * Created on October 25, 2013, 11:05 PM
 */

#ifndef MOVE_ENTITY_EVENT_H
#define	MOVE_ENTITY_EVENT_H

#include "Event.hpp"
#include "../logic/MobileEntity.h"

namespace gs {

class MoveEntityEvent : public Event {
public:
	MoveEntityEvent(Direction _direction) : direction(_direction) {}

	virtual EventEnum getType() const {
		return MOVE_ENTITY_EVENT;
	}

	Direction getDirection() const {
		return direction;
	}

private:
	Direction direction;
};

}

#endif	/* MOVE_ENTITY_EVENT_H */

