/* 
 * File:   MobileEntity.cpp
 * Author: williampoynter
 * 
 * Created on October 4, 2013, 12:23 AM
 */

#include "MobileEntity.h"

#include <cmath>

#include "../util/Logger.h"

using namespace gs;

MobileEntity::MobileEntity() : 
Entity(),
velocity(0,0),
force(0,0) {
}

MobileEntity::MobileEntity(const MobileEntity& orig) : Entity(orig) {
	max_speed = orig.getMaxSpeed();
	mass = orig.getMass();
	friction = orig.getFriction();
	setGeo(orig.getGeo());
	
}

MobileEntity::~MobileEntity() {
}

float MobileEntity::getMaxSpeed() const {
	return max_speed;
}

void MobileEntity::setMaxSpeed(float _max_speed) {
	max_speed = _max_speed;
}

sf::Vector2f MobileEntity::getVelocity() const {
	return velocity;
}

void MobileEntity::setVelocity(const sf::Vector2f &_velocity) {
	velocity = _velocity;
}

float MobileEntity::getMass() const {
	return mass;
}

void MobileEntity::setMass(float _mass) {
	mass = _mass;
}

sf::Vector2f MobileEntity::getFriction() const {
	return friction;
}

void MobileEntity::setFriction(const sf::Vector2f &_friction) {
	friction = _friction;
}

sf::Vector2f MobileEntity::getForce() const {
	return force;
}

void MobileEntity::setForce(const sf::Vector2f &_force) {
	force = _force;
}

sf::Vector2f MobileEntity::getVector(const Direction &dir, const float &mag) const {
	sf::Vector2f vector;
	
	float x_mag = mag;
	float y_mag = mag;

	const float rootTwoOverTwo = 0.70710678118;

	switch(dir) {
		case UP :
			y_mag *= -1;
		case DOWN :
			x_mag = 0;
			break;
		case LEFT :
			x_mag *= -1;
		case RIGHT :
			y_mag = 0;
			break;
		case UPRIGHT :
			x_mag *= -1;
		case DOWNRIGHT :
			x_mag *= rootTwoOverTwo;
			y_mag *= rootTwoOverTwo;
			break;
		case UPLEFT :
			x_mag *= -1;
		case DOWNLEFT :
			x_mag *= rootTwoOverTwo;
			y_mag *= -rootTwoOverTwo;
			break;
		case NONE :
			x_mag = 0;
			y_mag = 0;
			break;
	}
	
	vector.x = x_mag;
	vector.y = y_mag;
	return vector;
}

void MobileEntity::move(const double& dt) {
	/*sf::Vector2f vector = getVector(dt);

	geo.left = vector.x;
	geo.top = vector.y;*/
}

void MobileEntity::integrate(const double& dt) {
		
	state[0] = state[1];
	state[1] = state[2];
	
	double A = pow(dt,2) / mass;
	
	//Max Speed
	sf::Vector2f applied_force;
	sf::Vector2f applied_friction;
	if (fabs(velocity.x) > max_speed && fabs(force.x) > fabs(friction.x)) {
		applied_force.x = -friction.x;
	} else {
		applied_force.x = force.x;
	}
	if (fabs(velocity.y) > max_speed && fabs(force.y) > fabs(friction.y)) {
		applied_force.y = -friction.y;
	} else {
		applied_force.y = force.y;
	}
	
	if (fabs(velocity.x) < 0.000002 && applied_friction.x == 0) {
		state[0].x = state[1].x;
	}
	if (fabs(velocity.y) < 0.000002 && applied_friction.y == 0) {
		state[0].y = state[1].y;
	}

	if (fabs(velocity.x) < 0.000002) {
		applied_friction.x = 0;
	} else {
		applied_friction.x = -1 * (velocity.x/fabs(velocity.x)) * friction.x;
	}
	if (fabs(velocity.y) < 0.000002) {
		applied_friction.y = 0;
	} else {
		applied_friction.y = -1 * (velocity.y/fabs(velocity.y)) * friction.y;
	}
	
	state[2].x = (2 * state[1].x) - state[0].x + (A * (applied_force.x + applied_friction.x));
	state[2].y = (2 * state[1].y) - state[0].y + (A * (applied_force.y + applied_friction.y));
	
	velocity.x = (state[2].x - state[0].x)/ (2 * dt);
	velocity.y = (state[2].y - state[0].y)/ (2 * dt);
	

	DBG << "integrate applied_force x:" << applied_force.x << "\t y: " << applied_force.y << std::endl;
	DBG << "integrate applied_friction x:" << applied_friction.x << "\t y: " << applied_friction.y << std::endl;
	DBG << "integrate velocity x:" << velocity.x << "\t y: " << velocity.y << std::endl;
	
	DBG << "integrate state[0] x:" << state[0].x << "\t y: " << state[0].y << std::endl;
	DBG << "integrate state[1] x:" << state[1].x << "\t y: " << state[1].y << std::endl;
	DBG << "integrate state[2] x:" << state[2].x << "\t y: " << state[2].y << std::endl;
}

void MobileEntity::interpolate(const double& alpha) {
	geo.left = state[2].x * alpha + state[1].x * (1. - alpha);
	geo.top = state[2].y * alpha + state[1].y * (1. - alpha);
}

bool MobileEntity::detectCollision(const Entity &entity) {
	return geo.intersects(entity.getGeo());
}

void MobileEntity::setPosition(const sf::Vector2f& pos) {
	Entity::setPosition(pos);
	state[0] = state[1] = state[2] = pos;
}

void MobileEntity::setPosition(float x, float y) {
	Entity::setPosition(x,y);
	state[0] = state[1] = state[2] = sf::Vector2f(x,y);
}

void MobileEntity::setGeo(const sf::FloatRect& _geo) {
	Entity::setGeo(_geo);
	state[0] = state[1] = state[2] = sf::Vector2f(_geo.left,_geo.top);
}

void MobileEntity::setGeo(float x, float y, float w, float h) {
	Entity::setGeo(x,y,w,h);
	state[0] = state[1] = state[2] = sf::Vector2f(x,y);
}

bool MobileEntity::hasMoved() {
	return state[1] != state[2];
}