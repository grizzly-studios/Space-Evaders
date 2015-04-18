/* 
 * File:   KeyboardListener.h
 * Author: williampoynter
 *
 * Created on October 13, 2013, 9:55 AM
 */

#ifndef KEYBOARDLISTENER_H
#define	KEYBOARDLISTENER_H

#include "IKeyboardListener.h"

#include <array>

#include <SFML/Window/Keyboard.hpp>

#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"

#include "../event/ChangePlayerDirectionEvent.h"
#include "../event/GameStateChangedEvent.h"
#include "../event/GameEndEvent.h"
#include "../event/MenuActionEvent.h"

#include "../app/GameState.h"
#include "../logic/MobileEntity.h"

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
	std::array<bool, sf::Keyboard::KeyCount> previousState;
	
	void onGameStateChanged(GameStateChangedEvent &event);
	
	void inGameUpdate();
	void pausedUpdate();
	void loadingUpdate();
	void menuUpdate();
	void gameOverUpdate();
};

}

#endif	/* KEYBOARDLISTENER_H */

