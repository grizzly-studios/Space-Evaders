/* 
 * File:   MobileEntity.cpp
 * Author: williampoynter
 * 
 * Created on October 4, 2013, 12:23 AM
 */

#include "MobileEntity.h"

using namespace gs;

MobileEntity::MobileEntity() : Entity() {
}

MobileEntity::MobileEntity(const MobileEntity& orig) : Entity(orig) {
    mag = orig.getMagnitude();
    dir = orig.getDirection();
}

MobileEntity::~MobileEntity() {
}

float MobileEntity::getMagnitude() const {
    return mag;
}

void MobileEntity::setMagnitude(float _mag) {
    mag = _mag;
}

Direction MobileEntity::getDirection() const {
    return dir;
}

void MobileEntity::setDirection(Direction _dir) {
    dir = _dir;
}

void MobileEntity::move(const double& dt) {
    float x_mag = mag;
    float y_mag = mag;
    
    const float rootTwoOverTwo = 0.70710678118;
    
    switch(dir) {
	case UP :
	    y_mag *= -1;
	case DOWN :
	    x_mag = 0;
	    break;
	case LEFT :
	    x_mag *= -1;
	case RIGHT :
	    y_mag = 0;
	    break;
	case UPRIGHT :
	    x_mag *= -1;
	case DOWNRIGHT :
	    x_mag *= rootTwoOverTwo;
	    y_mag *= rootTwoOverTwo;
	    break;
	case UPLEFT :
	    x_mag *= -1;
	case DOWNLEFT :
	    x_mag *= rootTwoOverTwo;
	    y_mag *= -rootTwoOverTwo;
	    break;
	case NONE :
	    x_mag = 0;
	    y_mag = 0;
	    break;
    }
    
    position.x = x_mag * dt;
    position.y = y_mag * dt;
}

void MobileEntity::integrate(const double& dt) {
    float x_mag = mag;
    float y_mag = mag;
    
    const float rootTwoOverTwo = 0.70710678118;
    
    switch(dir) {
	case UP :
	    y_mag *= -1;
	case DOWN :
	    x_mag = 0;
	    break;
	case LEFT :
	    x_mag *= -1;
	case RIGHT :
	    y_mag = 0;
	    break;
	case UPRIGHT :
	    x_mag *= -1;
	case DOWNRIGHT :
	    x_mag *= rootTwoOverTwo;
	    y_mag *= rootTwoOverTwo;
	    break;
	case UPLEFT :
	    x_mag *= -1;
	case DOWNLEFT :
	    x_mag *= rootTwoOverTwo;
	    y_mag *= -rootTwoOverTwo;
	    break;
	case NONE :
	    x_mag = 0;
	    y_mag = 0;
	    break;
    }
	
	state[0] = state[1];
	
	state[1].x = x_mag * dt;
    state[1].y = y_mag * dt;
}

void MobileEntity::interpolate(const double& alpha) {
	position.x = state[1].x * alpha + state[0].x * (1. - alpha);
	position.y = state[1].y * alpha + state[0].y * (1. - alpha);
}