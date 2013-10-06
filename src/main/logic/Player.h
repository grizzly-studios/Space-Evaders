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

	class Player : public MobileEntity {
	public:
		Player();
		Player(const Player& orig);
		virtual ~Player();
	private:

	};

}

#endif	/* PLAYER_H */

