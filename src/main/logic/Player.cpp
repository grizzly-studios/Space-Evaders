/* 
 * File:   Player.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:49 AM
 */

#include "Player.h"

using namespace gs;

std::list<PlayerShPtr> Player::all;

Player::Player() :
		MobileEntity() {
	//Setting default behaviour for player
	name = "Player 1";
	max_speed = 200.f/1000000.f;	// unit: pixel/microseconds
	mass = 100000;
	friction.x = 25.f/1000000.f;
	friction.y = 25.f/1000000.f;
	lives = 3;
	score = 0;
	effects.push_back(newFrictionMultiplierShPtr(this, 4000000, 0.5));
	effectForce = sf::Vector2f(0,0);
	beenHit = false;
	invincible = false;
}

Player::Player(const Player& orig) : MobileEntity(orig) {
	score = orig.score;
	lives = orig.lives;
	invincible = orig.invincible;
}

Player::~Player()  {
	DBG << "Player destroyed:" << getID() << std::endl;
}

PlayerShPtr Player::create() {
	all.push_back(PlayerShPtr(new Player()));
	MobileEntity::all.push_back(all.back());
	Entity::all.push_back(all.back());
	return all.back();
}

void Player::destroy(unsigned int _ID) {
	all.remove_if(cleaner(_ID));
	MobileEntity::all.remove_if(cleaner(_ID));
	Entity::all.remove_if(cleaner(_ID));
}

void Player::destroy() {
	destroy(getID());
}

void Player::tick(const long int &deltaTime) {

	//Runs the effects
	for (IEffectShPtr effect : effects) {
		(*effect)(deltaTime);
	}
	//Removes all expired effects
	::clean(effects);

	MobileEntity::tick(deltaTime);

	for (EntityShPtr entity : Entity::all) {
		if (entity->getName() == "Bullets") {
			if (detectCollision(*entity)) {
				DBG << "Player ID " << getID() << " has been hit. Lives had: " << lives << std::endl;
				hit();
				toRemove.push_back(entity);
				break;
			}
		}
	}

	sf::Vector2f offset;
	if (isOutOfBounds(sf::FloatRect(
		GBL::SCREEN_SPRITE_WIDTH,
		GBL::SCREEN_SPRITE_WIDTH,
		GBL::WIDTH - (GBL::SCREEN_SPRITE_WIDTH * 2),
		GBL::HEIGHT - (GBL::SCREEN_SPRITE_WIDTH * 2)),offset)) {
		if (offset.x > 0) {
			disableDir(RIGHT);
		} else if (offset.x < 0) {
			disableDir(LEFT);
		} else if (offset.y > 0) {
			disableDir(DOWN);
		}
	} else {
		enableAllDir();
	}
}

void Player::hit(){
	if (!invincible) {
		lifeDown();
		beenHit = true;
		effects.push_back(newInvincibleShPtr(this, 3000000));
	}
}

void Player::integrate() {

	state[0] = state[1];
	state[1] = state[2];

	sf::Vector2f accel = acceleration(h, state, mass, max_speed, velocity, friction, force + effectForce);

	state[2].x = (2 * state[1].x) - state[0].x + (pow(h,2) * accel.x);
	state[2].y = (2 * state[1].y) - state[0].y + (pow(h,2) * accel.y);

	velocity.x = (state[2].x - state[0].x)/ (2 * h);
	velocity.y = (state[2].y - state[0].y)/ (2 * h);
}

bool Player::advancer(MobileEntityShPtr bullets) {
	if (prevPosition.y >= bullets->getPrevPosition().y && geo.top < bullets->getPosition().y) {
		effects.push_back(newForceShPtr(this, 300000, sf::Vector2f(0,-0.000005f)));
		scoreUp(10);
		return true;
	}
	return false;
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
	lives = 0;
}

bool Player::hasBeenHit(bool reset) {
	bool output = beenHit;
	if (reset) {
		beenHit = false;
	}
	return output;
}

void Player::scoreUp(int value){
	if(value > 0){
		score += value;
	} else {
		WARN << "Tried to raise score using zero or negative number (" << value <<"). Use scoreDown instead!" << std::endl;
	}
}

int Player::getScore() const {
	return score;
}
	
void Player::scoreDown(int value){
 	if(value > 0){
 		score -= value;
 	} else {
		WARN << "Tried to lower score using zero or negative number (" << value <<"). Use scoreUp instead!" << std::endl;
 	}
}

void Player::setInvincible(bool _invincible) {
	invincible = _invincible;
}

bool Player::isInvincible() {
	return invincible;
}
