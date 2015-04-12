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

#include "MobileEntity.h"
#include "Player.h"
#include "Bullets.h"
#include "Enemy.h"

#include "../util/RandomNumberGenerator.h"

#include "../app/GameState.h"
#include "../app/Globals.h"

namespace gs {

typedef std::list<EntityShPtr> EntityList;
typedef std::list<MobileEntityShPtr> MobileEntityList;
typedef std::list<PlayerShPtr> PlayerList;
typedef std::list<BulletsShPtr> BulletsList;

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
	double gameTime;
	RandomNumberGenerator randomNumberGenerator;
	double accumulator;

	EntityList allObjects;
	MobileEntityList mobileObjects;
	PlayerList allPlayers;
	BulletsList allBullets;
	EntityList toBeRemoved;

	int level;
	int wave;
	int numLives;
	double nextBulletSpawn;
	int bulletInterval;
	double advanceUntil;
	bool startAdvance;
	bool advancing;
	
	//Subroutines
	void move();
	void collisionDetection();
	void boundsCheck();
	void advancePlayers();
	void cleanUp();
	void spawn();

	void startNewGame();
	void gameEnd();
	void checkEnd();

	void integrate();
	void interpolate(const double &remainder);
	
	void onChangePlayerDirection(ChangePlayerDirectionEvent &event);
	void onGameStateChange(GameStateChangedEvent &event);
	
	void addBullets(sf::Vector2f velocity, sf::FloatRect geo);
	void generateBullets();
	void removeEntity(unsigned int entityID);
};

}

#endif	/* LOGIC_H */
