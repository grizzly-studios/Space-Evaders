#ifndef MAIN_LOOP_H
#define	MAIN_LOOP_H

#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "IGameState.h"

#include "../event/IEventListener.hpp"

namespace gs {

typedef std::shared_ptr<sf::RenderWindow> RenderWindowShPtr;

class MainLoop : public IEventListener {
public:
	MainLoop(std::map<GameState, IGameStateShPtr> _gameStates, RenderWindowShPtr _window);
	void run();

	virtual void onEvent(Event& event);

private:
	void changeStateIfPending();

	std::map<GameState, IGameStateShPtr> gameStates;
	RenderWindowShPtr window;
	IGameStateShPtr currentState;
	IGameStateShPtr nextState;
};

}

#endif	/* MAIN_LOOP_H */
