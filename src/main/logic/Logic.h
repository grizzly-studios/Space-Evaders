#ifndef LOGIC_H
#define	LOGIC_H

#include <iostream>
#include <list>
#include <algorithm>
#include <iomanip>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "ILogic.hpp"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"
#include "../event/EntityCreatedEvent.hpp"
#include "../event/EntityDeletedEvent.hpp"
#include "../event/EntityMovedEvent.hpp"
#include "../event/ChangePlayerDirectionEvent.h"
#include "../event/GameStateChangedEvent.h"
#include "../event/ScoreChangedEvent.hpp"

#include "MobileEntity.h"
#include "Player.h"
#include "Bullets.h"
#include "Enemy.h"

#include "../util/RandomNumberGenerator.h"

#include "../app/GameState.h"
#include "../app/Globals.h"

namespace gs {

class Logic : public ILogic, public IEventListener  {
public:
	Logic(IEventManagerPtr _eventManager);
	~Logic();
	virtual void update(long int elapsed);
	virtual void onEvent(Event& event);
	
	virtual void generateLevel();
	
private:
	IEventManagerPtr eventManager;
	GameState gameState;
	
	sf::Clock *clock;
	RandomNumberGenerator randomNumberGenerator;
	double accumulator;

	EntityList toBeRemoved;

	int level;
	int wave;
	double nextBulletSpawn;
	int bulletInterval;
	double advanceUntil;
	bool startAdvance;
	bool advancing;

	int endCount;
	
	//Subroutines
	void advancePlayers();
	void cleanUp();
	void spawn();

	void startNewGame();
	void gameEnd();
	void checkEnd();
	
	void onChangePlayerDirection(ChangePlayerDirectionEvent &event);
	void onGameStateChange(GameStateChangedEvent &event);
	
	void addBullets(sf::Vector2f velocity, sf::FloatRect geo);
	void generateBullets();
};

}

#endif	/* LOGIC_H */
