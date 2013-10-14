/* 
 * File:   Obstacle.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:59 AM
 */

#include "Obstacle.h"

using namespace gs;

Obstacle::Obstacle() : Entity() {
	name = "Obstacle";
}

Obstacle::Obstacle(const Obstacle& orig) : Entity(orig) {
}

Obstacle::~Obstacle() {
}

