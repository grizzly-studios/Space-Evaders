/* 
 * File:   Bullets.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:44 AM
 */

#include "Bullets.h"

using namespace gs;

Bullets::Bullets() : MobileEntity() {
    name = "Bullets";
    mag = 10;
    dir = DOWN;
}

Bullets::Bullets(Direction _dir, float _mag) : MobileEntity() {
    dir = _dir;
    mag = _mag;
}

Bullets::Bullets(const Bullets& orig) : MobileEntity(orig) {
}

Bullets::~Bullets() {
}
