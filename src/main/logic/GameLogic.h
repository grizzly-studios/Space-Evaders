/* 
 * File:   GameLogic.h
 * Author: williampoynter
 *
 * Created on October 5, 2013, 3:40 PM
 */

#ifndef GAMELOGIC_H
#define	GAMELOGIC_H

#include <list>
#include <algorithm>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "MobileEntity.h"
#include "Player.h"
#include "Bullets.h"

namespace gs {

	typedef std::list<EntityShPtr> EntityList;
	typedef std::list<MobileEntityShPtr> MobileEntityList;
	typedef std::list<PlayerShPtr> PlayerList;
	typedef std::list<BulletsShPtr> BulletsList;
	
	class GameLogic {
	public:
		GameLogic();
		~GameLogic();
		
		void init();
		void update();
	private:
		sf::Clock *clock;
		double accumulator;
		double dt;
		
		EntityList allObjects;
		MobileEntityList mobileObjects;
		PlayerList allPlayers;
		BulletsList allBullets;
		
		void integrate();
		void interpolate(const double &remainder);
	};

}

#endif	/* GAMELOGIC_H */

