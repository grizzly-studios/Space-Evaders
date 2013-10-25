/* 
 * File:   StateChangedEvent.h
 * Author: williampoynter
 *
 * Created on October 25, 2013, 9:56 PM
 */

#ifndef STATE_CHANGED_EVENT_H
#define	STATE_CHANGED_EVENT_H

#include "Event.hpp"
#include "../app/GameState.h"

namespace gs {
	
class StateChangedEvent : public Event {
public:
	StateChangedEvent(GameState _newState) : newState(_newState) {}
	
	virtual EventEnum getType() const {
		return GAME_STATE_CHANGED_EVENT;
	}
	
	GameState getState() const {
		return newState;
	}
	
private:
	GameState newState;
	
};

}

#endif	/* STATE_CHANGED_EVENT_H */

