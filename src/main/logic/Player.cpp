/* 
 * File:   Player.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:49 AM
 */

#include "Player.h"

using namespace gs;

Player::Player(double *_gameTime) :
		MobileEntity(),
		state(PlayerState::ALIVE),
		gameTime(_gameTime) {
	//Setting default behaviour for player
	name = "Player 1";
	max_speed = 200.f/1000000.f;	// unit: pixel/microseconds
	mass = 100000;
	friction.x = 25.f/1000000.f;
	friction.y = 25.f/1000000.f;
	lives = 3;
	score = 0;
}

Player::Player(const Player& orig) : MobileEntity(orig) {
	score = orig.score;
	lives = orig.lives;
	state = orig.state;
	gameTime = orig.gameTime;
}

Player::~Player()  {
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

PlayerState Player::getState() const {
	return state;
}

void Player::hit(){
	lifeDown();
	//Set up immunity later
}

void Player::integrate(){
	for (PlayerEffect effect : effects) {
		(*effect)(this);
	}
	clean(effects, gameTime);

	MobileEntity::integrate();
}

void Player::lifeUp(){
	lives++;
}
	
void Player::lifeDown(){
	lives--;
}

int Player::livesLeft(){
	return lives;
}

void Player::kill(){
	hit();
	lives = 0;
}

void Player::scoreUp(int value){
	if(value > 0){
		score += value;
	} else {
		WARN << "Tried to raise score using zero or negative number (" << value <<"). Use scoreDown instead!" << std::endl;
	}
}
	
void Player::scoreDown(int value){
 	if(value > 0){
 		score -= value;
 	} else {
		WARN << "Tried to lower score using zero or negative number (" << value <<"). Use scoreDown instead!" << std::endl;
 	}
}

void Player::respawn(){
	state = PlayerState::ALIVE;
}

bool Player::isAlive(){
	return state == PlayerState::ALIVE;
}

bool Player::isHit(){
	return state == PlayerState::HIT;
}

bool Player::isDead(){
	return state == PlayerState::DEAD;
}
