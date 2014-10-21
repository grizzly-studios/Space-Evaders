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
	mag = 100.f/1000000.f;	// unit: pixel/microseconds
}

Player::Player(const Player& orig) : MobileEntity(orig) {
}

Player::~Player() {
}

Direction Player::isOutOfBounds(){
	short boundsBreach = 0; /* Bits are as follows Top (8), Left (4), Right (2), Bot (1) */
	sf::FloatRect pos = getGeo();

	if(pos.left <= (GBL::SCREEN_SPRITE_WIDTH + 2)){
		//Too far left
		boundsBreach |= 4;
	}

	if((pos.left + pos.width) >= (GBL::WIDTH - (GBL::SCREEN_SPRITE_WIDTH + 2))){
		//Too far right
		boundsBreach |= 2;
	}

	if(pos.top <= (GBL::SCREEN_SPRITE_WIDTH + 2)){
		//Too far up
		boundsBreach |= 8;
	}

	if((pos.top + pos.height) >= (GBL::HEIGHT - (GBL::SCREEN_SPRITE_WIDTH + 2))){
		//Too far down
		boundsBreach |= 1;
	}
	
	return (MobileEntity::shortToDirection(boundsBreach));
}

