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
	Player();
	Player(const Player& orig);
	virtual ~Player();

	virtual PlayerState getState() const;

	Direction isOutOfBounds();

	void hit();
	void tick();
private:
	PlayerState curState;
	int curtick;
	int hitTick;
};

typedef std::shared_ptr<Player> PlayerShPtr;

}

#endif	/* PLAYER_H */

