/* 
 * File:   GameEndEvent.h
 * Author: rob parker
 *
 * Created on November 19, 2013, 20:22 PM
 */

#ifndef GAME_END_EVENT_H
#define	GAME_END_EVENT_H

#include "Event.hpp"

namespace gs {

class GameEndEvent : public Event {
public:
	GameEndEvent () {}

	virtual EventEnum getType() const {
		return GAME_END_EVENT;
	}

private:
};

}

#endif	/* GAME_END_EVENT_H */

