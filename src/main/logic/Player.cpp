/* 
 * File:   Player.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:49 AM
 */

#include "Player.h"

using namespace gs;

Player::Player() : MobileEntity() {
	name = "Player 1";
	dir = NONE;
	mag = 100;
}

Player::Player(const Player& orig) : MobileEntity(orig) {
}

Player::~Player() {
}

