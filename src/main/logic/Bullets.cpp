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
    dir = Direction::DOWN;
}

Bullets::Bullets(const Bullets& orig) : MobileEntity(orig) {
    mag = orig.getMagnitude();
    dir = orig.getDirection();
}

Bullets::~Bullets() {
}

float Bullets::getMagnitude() const {
    return mag;
}

void Bullets::setMagnitude(float _mag) {
    mag = _mag;
}

Direction Bullets::getDirection() const {
    return dir;
}

void Bullets::setDirection(Direction _dir) {
    dir = _dir;
}

void Bullets::move(const double& dt) {
    float x_mag = mag;
    float y_mag = mag;
    
    const float rootTwoOverTwo = 0.70710678118;
    
    switch(dir) {
	case Direction::UP :
	    y_mag *= -1;
	case Direction::DOWN :
	    x_mag = 0;
	    break;
	case Direction::LEFT :
	    x_mag *= -1;
	case Direction::RIGHT :
	    y_mag = 0;
	    break;
	case Direction::UPRIGHT :
	    x_mag *= -1;
	case Direction::DOWNRIGHT :
	    x_mag *= rootTwoOverTwo;
	    y_mag *= rootTwoOverTwo;
	    break;
	case Direction::UPLEFT :
	    x_mag *= -1;
	case Direction::DOWNLEFT :
	    x_mag *= rootTwoOverTwo;
	    y_mag *= -rootTwoOverTwo;
	    break;
    }
    
    position.x = x_mag * dt;
    position.y = y_mag * dt;
}