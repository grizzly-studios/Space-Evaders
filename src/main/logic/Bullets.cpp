/* 
 * File:   Bullets.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:44 AM
 */

#include "Bullets.h"

using namespace gs;

Bullets::Bullets() : MobileEntity() {
	//Setting default behaviour for bullets
	name = "Bullets";
	max_speed = 100.f/1000000.f;	// unit: pixel/microseconds
	mass = 100000;
	friction.x = 25.f/1000000.f;
	friction.y = 0.f;
}

Bullets::Bullets(sf::Vector2f velocity) : MobileEntity() {
	name = "Bullets";
	max_speed = 100.f/1000000.f;	// unit: pixel/microseconds
	mass = 100000;
	friction.x = 25.f/1000000.f;
	friction.y = 0.f;
	setVelocity(velocity);
}

Bullets::Bullets(const Bullets& orig) : MobileEntity(orig) {
}

Bullets::~Bullets() {
}

Direction Bullets::isOutOfBounds(){
	sf::FloatRect pos = getGeo();

	/* No Top, Left or Right check as Bullets only move down */
	if((pos.top + pos.height) >= (GBL::HEIGHT - (GBL::SCREEN_SPRITE_WIDTH + 2))){
		//Too far down
		return DOWN;
	} else{
		return NONE;
	}

	
}
