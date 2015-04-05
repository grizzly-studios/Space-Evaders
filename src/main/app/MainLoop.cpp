#include "MainLoop.h"

#include "../event/GameStateChangedEvent.h"

#include "../util/Logger.h"

using namespace gs;

MainLoop::MainLoop(std::map<GameState, IGameStateShPtr> _gameStates, RenderWindowShPtr _window)
	: gameStates(_gameStates),
	  window(_window),
	  currentState(nullptr),
	  nextState(nullptr) {
}

void MainLoop::run() {
	INFO << "Beginning while loop" << std::endl;

	while(window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}

		currentState->handleInput();
		changeStateIfPending();

		currentState->update();
		changeStateIfPending();

		currentState->render();
	}
}

void MainLoop::onEvent(Event& event) {
	INFO << "Received event: " << event << std::endl;

	if (GAME_STATE_CHANGED_EVENT == event.getType()) {
		GameStateChangedEvent& gameStateChanged = (GameStateChangedEvent&) event;

		nextState = gameStates.at(gameStateChanged.getState());
	}
}

void MainLoop::changeStateIfPending() {
	if (nextState != nullptr) {
        currentState = nextState;
        nextState = nullptr;
    }
}
