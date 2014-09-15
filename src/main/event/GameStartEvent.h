/* 
 * File:   GameStartEvent.h
 * Author: rob parker
 *
 * Created on November 19, 2013, 20:22 PM
 */

#ifndef GAME_START_EVENT_H
#define	GAME_START_EVENT_H

#include "Event.hpp"

namespace gs {

class GameStartEvent : public Event {
public:
	GameStartEvent () {}

	virtual EventEnum getType() const {
		return GAME_START_EVENT;
	}

private:
};

}

#endif	/* GAME_START_EVENT_H */

