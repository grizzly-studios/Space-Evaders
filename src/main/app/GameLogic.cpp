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

void GameLogic::evaluate() {
    sf::Time elapsed = clock->restart();
    accumulator += elapsed.asMicroseconds();
    
    while(accumulator >= dt) {
		integrate();
		accumulator -= dt;
    }
    
    interpolate(accumulator);
}

void GameLogic::integrate() {
    for (mobs::iterator it = mobileObjects.begin(); it != mobileObjects.end(); it++) {
		(*it)->integrate(dt);
	}
}

void GameLogic::interpolate(const double &remainder) {
	const double alpha  = remainder / dt;
	for (mobs::iterator it = mobileObjects.begin(); it != mobileObjects.end(); it++) {
		(*it)->interpolate(alpha);
	}
}