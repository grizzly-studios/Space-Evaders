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
    mag = 100.f/1000000.f;	// unit: pixel/microseconds
    dir = DOWN;
}

Bullets::Bullets(Direction _dir, float _mag) : MobileEntity() {
	name = "Bullets";
    dir = _dir;
    mag = _mag;
}

Bullets::Bullets(const Bullets& orig) : MobileEntity(orig) {
}

Bullets::~Bullets() {
}
