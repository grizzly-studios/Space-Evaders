/* 
 * File:   Bullets.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:44 AM
 */

#include "Bullets.h"

using namespace gs;

std::list<BulletsShPtr> Bullets::all;

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
	DBG << "Bullets de-constructed" << std::endl;
}

BulletsShPtr Bullets::create() {
	all.push_back(BulletsShPtr(new Bullets()));
	MobileEntity::all.push_back(all.back());
	Entity::all.push_back(all.back());
	return all.back();
}

BulletsShPtr Bullets::create(sf::Vector2f velocity) {
	all.push_back(BulletsShPtr(new Bullets(velocity)));
	MobileEntity::all.push_back(all.back());
	Entity::all.push_back(all.back());
	return all.back();
}

void Bullets::tick(const long int &deltaTime) {

	MobileEntity::tick(deltaTime);

	Direction oOB = isOutOfBounds();
	if(oOB == DOWN){
		DBG << "Bullet ID " << getID() << " is out of bounds. Adding to remove list." << std::endl;
		toRemove.push_back(shared_from_this());
	}
}

void Bullets::destroy(unsigned int _ID) {
	all.remove_if(cleaner(_ID));
	MobileEntity::all.remove_if(cleaner(_ID));
	Entity::all.remove_if(cleaner(_ID));
}

void Bullets::destroy() {
	destroy(getID());
}

Direction Bullets::isOutOfBounds(){
	sf::FloatRect pos = getGeo();

	/* No Top, Left or Right check as Bullets only move down */
	if(pos.top >= (GBL::HEIGHT - (GBL::SCREEN_SPRITE_WIDTH + 2))){
		//Too far down
		return DOWN;
	} else{
		return NONE;
	}

	
}
