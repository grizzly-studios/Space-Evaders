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
#include "IEffect.h"

namespace gs {

enum class PlayerState {
	ALIVE,
	HIT,
	DEAD
};

class Player;

typedef IEffectShPtr<Player> PlayerEffect;
typedef IEffectList<Player> PlayerEffects;

class Player : public MobileEntity {
public:
	Player(double *_gameTime);
	Player(const Player& orig);
	virtual ~Player();

	virtual PlayerState getState() const;

	Direction isOutOfBounds();
	virtual void integrate();

	void hit();
	void lifeUp();
	void lifeDown();
	int livesLeft();
	void kill();

	void scoreUp(int value);
	void scoreDown(int value);
	int  getScore() const;

	bool isAlive();
	bool isHit();
	bool isDead();

	void respawn();
private:
	PlayerState state;
	double *gameTime;
	int score;
	int lives;
	PlayerEffects effects;
};

typedef std::shared_ptr<Player> PlayerShPtr;
}

#endif	/* PLAYER_H */

