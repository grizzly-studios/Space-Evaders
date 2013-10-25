/* 
 * File:   KeyboardListener.h
 * Author: williampoynter
 *
 * Created on October 13, 2013, 9:55 AM
 */

#ifndef KEYBOARDLISTENER_H
#define	KEYBOARDLISTENER_H

#include "IKeyboardListener.h"

#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"
#include "../app/GameState.h"
#include "../event/GameStateChangedEvent.h"

namespace gs {

class KeyboardListener : public IKeyboardListener, public IEventListener {
public:
	KeyboardListener(IEventManagerPtr _eventManager);
	virtual ~KeyboardListener();
	
	virtual void onEvent(Event& event);
	
	virtual void update();
private:
	IEventManagerPtr eventManager;
	GameState gameState;
	
	void onGameStateChanged(GameStateChangedEvent &event);
};

}

#endif	/* KEYBOARDLISTENER_H */

