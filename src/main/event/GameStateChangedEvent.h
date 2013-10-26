/* 
 * File:   GameStateChangedEvent.h
 * Author: williampoynter
 *
 * Created on October 25, 2013, 9:56 PM
 */

#ifndef GAME_STATE_CHANGED_EVENT_H
#define	GAME_STATE_CHANGED_EVENT_H

#include "Event.hpp"
#include "../app/GameState.h"

namespace gs {
	
class GameStateChangedEvent : public Event {
public:
	GameStateChangedEvent(GameState _newState) : newState(_newState) {}
	
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

#endif	/* GAME_STATE_CHANGED_EVENT_H */

