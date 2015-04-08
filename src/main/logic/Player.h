/* 
 * File:   Player.h
 * Author: williampoynter
 *
 * Created on October 5, 2013, 9:49 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "MobileEntity.h"
#include "../util/Logger.h"
#include "../app/Globals.h"
#include "../event/EntityCreatedEvent.hpp"
#include "../event/IEventManager.hpp"

namespace gs {

enum class PlayerState {
	ALIVE,
	HIT,
	DEAD
};

class Player : public MobileEntity {
public:
	Player(IEventManagerPtr _eventManager, double *gameTime);
	Player(const Player& orig, double *gameTime);
	virtual ~Player();

	virtual PlayerState getState() const;

	Direction isOutOfBounds();

	void hit();
	void refresh();
	void lifeUp();
	void lifeDown();
	int livesLeft();
	void kill();
	void scoreUp(int value);
	void scoreDown(int value);
	int  getScore();
	bool isAlive();
	bool isHit();
	bool isDead();
	void respawn();
private:
	IEventManagerPtr eventManager;
	PlayerState curState;
	double hitTick;
	double *tick;
	int score;
	int lives;
};

typedef std::shared_ptr<Player> PlayerShPtr;

}

#endif	/* PLAYER_H */

