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
}

Bullets::Bullets(float _max_speed) : MobileEntity() {
	name = "Bullets";
    max_speed = _max_speed;
}

Bullets::Bullets(const Bullets& orig) : MobileEntity(orig) {
}

Bullets::~Bullets() {
}
