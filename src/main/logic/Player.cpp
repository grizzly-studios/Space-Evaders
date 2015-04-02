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
	max_speed = 200.f/1000000.f;	// unit: pixel/microseconds
	mass = 100000;
	friction.x = 25.f/1000000.f;
	friction.y = 25.f/1000000.f;
}

Player::Player(const Player& orig) : MobileEntity(orig) {
}

Player::~Player() {
}

