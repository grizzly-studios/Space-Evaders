/* 
 * File:   ChangePlayerDirectionEvent.h
 * Author: rob parker
 *
 * Created on November 19, 2013, 20:22 PM
 */

#ifndef CHANGE_PLAYER_DIRECTION_EVENT_H
#define	CHANGE_PLAYER_DIRECTION_EVENT_H

#include "Event.hpp"
#include "../logic/MobileEntity.h"

namespace gs {

class GameStartEvent : public Event {
public:
	GameStartEvent (){};

	virtual EventEnum getType() const {
		return GAME_START_EVENT;
	}

private:
};

}

#endif	/* CHANGE_PLAYER_DIRECTION_EVENT_H */

