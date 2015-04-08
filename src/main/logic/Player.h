/* 
 * File:   Player.h
 * Author: williampoynter
 *
 * Created on October 5, 2013, 9:49 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "MobileEntity.h"

namespace gs {

enum class PlayerState {
	ALIVE,
	HIT,
	DEAD
};

class Player : public MobileEntity {
public:
	Player(double *gameTime);
	Player(const Player& orig, double *gameTime);
	virtual ~Player();

	virtual PlayerState getState() const;

	Direction isOutOfBounds();

	void hit();
	void refresh();
private:
	PlayerState curState;
	double hitTick;
	double *tick;
};

typedef std::shared_ptr<Player> PlayerShPtr;

}

#endif	/* PLAYER_H */

