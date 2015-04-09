/* 
 * File:   Player.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:49 AM
 */

#include "Player.h"
#include "../util/Logger.h"

using namespace gs;

Player::Player(double *_gameTime) :
		MobileEntity(),
		gameTime(_gameTime) {
	//Setting default behaviour for player
	name = "Player 1";
	max_speed = 200.f/1000000.f;	// unit: pixel/microseconds
	mass = 100000;
	friction.x = 25.f/1000000.f;
	friction.y = 25.f/1000000.f;
	lives = 3;
	score = 0;
	effects.push_back(newFrictionMultiplierShPtr(this, _gameTime, 4000, 0.5));
}

Player::Player(const Player& orig) : MobileEntity(orig) {
	score = orig.score;
	lives = orig.lives;
	gameTime = orig.gameTime;
	invincible = orig.invincible;
	hidden = orig.hidden;
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

void Player::hit(){
	if (!invincible) {
		lifeDown();
		effects.push_back(newInvincibleShPtr(this, gameTime, 3000));
	}
}

void Player::integrate(){
	//Runs the effects
	for (IEffectShPtr effect : effects) {
		(*effect)();
	}
	//Removes all expired effects
	clean(effects);

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

void Player::setInvincible(bool _invincible) {
	invincible = _invincible;
}

bool Player::isInvincible() {
	return invincible;
}

void Player::setHidden(bool _hidden) {
	hidden = _hidden;
}

bool Player::isHidden() {
	return hidden;
}
