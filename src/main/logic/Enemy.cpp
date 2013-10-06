/* 
 * File:   Enemy.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:53 AM
 */

#include "Enemy.h"

using namespace gs;

Enemy::Enemy() : Entity() {
    name = "Enemy";
}

Enemy::Enemy(const Enemy& orig) : Entity(orig) {
}

Enemy::~Enemy() {
}

