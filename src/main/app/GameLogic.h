/* 
 * File:   GameLogic.h
 * Author: williampoynter
 *
 * Created on October 5, 2013, 3:40 PM
 */

#ifndef GAMELOGIC_H
#define	GAMELOGIC_H

#include <list>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "../logic/MobileEntity.h"

namespace gs {

	typedef std::list<MobileEntity*> mobs;	
	
	class GameLogic {
	public:
		GameLogic();
		~GameLogic();
		
		void init();
		void evaluate();
	private:
		sf::Clock *clock;
		double accumulator;
		double dt;
		
		mobs mobileObjects;
		
		void integrate();
		void interpolate(const double &remainder);
	};

}

#endif	/* GAMELOGIC_H */

