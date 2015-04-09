/* 
 * File:   Player.h
 * Author: williampoynter
 *
 * Created on October 5, 2013, 9:49 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "MobileEntity.h"
#include "effects/FrictionMultiplier.h"
#include "effects/Invincible.h"

namespace gs {

class Player : public MobileEntity {
public:
	Player(double *_gameTime);
	Player(const Player& orig);
	virtual ~Player();

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

	void setInvincible(bool _invincible);
	bool isInvincible();
	void setHidden(bool hidden);
	bool isHidden();

	void respawn();
private:
	double *gameTime;
	int score;
	int lives;
	IEffectList effects;

	bool invincible;
	bool hidden;
};

typedef std::shared_ptr<Player> PlayerShPtr;
}

#endif	/* PLAYER_H */

