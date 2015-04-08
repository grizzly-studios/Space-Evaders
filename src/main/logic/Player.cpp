/* 
 * File:   Player.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:49 AM
 */

#include "Player.h"

using namespace gs;

Player::Player(IEventManagerPtr _eventManager, double *gameTime) : MobileEntity(), 
                                eventManager(_eventManager), tick(gameTime) {
	//Setting default behaviour for player
	name = "Player 1";
	max_speed = 200.f/1000000.f;	// unit: pixel/microseconds
	mass = 100000;
	friction.x = 25.f/1000000.f;
	friction.y = 25.f/1000000.f;
	curState = PlayerState::ALIVE;
	lives = 3;
	score = 0;
	hitTick = 0;
}

Player::Player(const Player& orig, double *gameTime) : MobileEntity(orig), tick(gameTime) {
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
	return curState;
}

void Player::hit(){
	lifeDown();
	curState = PlayerState::HIT;
	hitTick = *tick;
}

void Player::refresh(){
	if(isHit()){
		if(*tick >= (hitTick + 1000)){
			if(lives > 0 ){
				respawn();
			} else {
				curState = PlayerState::DEAD;
			}
		}
	}
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

int Player::getScore(){
	return score;
}

void Player::respawn(){
	curState = PlayerState::ALIVE;
	EntityCreatedEvent entityCreatedEvent(getID(), PLAYER_ENTITY, getGeo());
	eventManager->fireEvent(entityCreatedEvent);
}

bool Player::isAlive(){
	return curState == PlayerState::ALIVE;
}

bool Player::isHit(){
	return curState == PlayerState::HIT;
}

bool Player::isDead(){
	return curState == PlayerState::DEAD; 
}