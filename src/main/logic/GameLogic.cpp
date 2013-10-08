/* 
 * File:   GameLogic.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 3:40 PM
 */

#include "GameLogic.h"

using namespace gs;

GameLogic::GameLogic() {
}

GameLogic::~GameLogic() {
}

void GameLogic::init() {
    clock = new sf::Clock();
    accumulator = 0;
    dt = 12500;
}

void GameLogic::update() {
    sf::Time elapsed = clock->restart();
    accumulator += elapsed.asMicroseconds();
    
	//Move objects
    while(accumulator >= dt) {
		integrate();
		accumulator -= dt;
    }
    interpolate(accumulator);
	
	//Detect collisions
	std::list<unsigned int> skip;			//List of IDs to skip
	//Scan for player collisions
	for (PlayerList::iterator it = allPlayers.begin(); it != allPlayers.end(); it++) {
		skip.push_back((*it)->getID());
		for (EntityList::iterator iter = allObjects.begin(); iter != allObjects.end(); iter++) {
			if (std::find(skip.begin(), skip.end(), (*iter)->getID()) == skip.end()) {
				/*Skipped collision check because a check has already been performed
				 * between these two entities.*/
				continue;
			}
			if((*it)->detectCollision(**iter)) {	//Collision
				//Fire player collision event
			}
		}
	}
	for (BulletsList::iterator it = allBullets.begin(); it != allBullets.end(); it++) {
		skip.push_back((*it)->getID());
		for (EntityList::iterator iter = allObjects.begin(); iter != allObjects.end(); iter++) {
			if (std::find(skip.begin(), skip.end(), (*iter)->getID()) == skip.end()) {
				/*Skipped collision check because a check has already been performed
				 * between these two entities.*/
				continue;
			}
			if ((*it)->detectCollision(**iter)) {	//Collision
				//Fire bullet collision event
			}
		}
	}
}

void GameLogic::integrate() {
    for (MobileEntityList::iterator it = mobileObjects.begin(); it != mobileObjects.end(); it++) {
		(*it)->integrate(dt);
	}
}

void GameLogic::interpolate(const double &remainder) {
	const double alpha  = remainder / dt;
	for (MobileEntityList::iterator it = mobileObjects.begin(); it != mobileObjects.end(); it++) {
		(*it)->interpolate(alpha);
	}
}