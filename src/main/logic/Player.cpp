/* 
 * File:   Player.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:49 AM
 */

#include "Player.h"

using namespace gs;

Player::Player() : MobileEntity() {
	//Setting default behaviour for player
	name = "Player 1";
	dir = NONE;
	mag = 100/1000000;	// unit: pixel/microseconds
}

Player::Player(const Player& orig) : MobileEntity(orig) {
}

Player::~Player() {
}

