/* 
 * File:   MobileEntity.cpp
 * Author: williampoynter
 * 
 * Created on October 4, 2013, 12:23 AM
 */

#include "MobileEntity.h"

using namespace gs;

MobileEntity::MobileEntity() : Entity() {
}

MobileEntity::MobileEntity(const MobileEntity& orig) : Entity(orig) {
	mag = orig.getMagnitude();
	dir = orig.getDirection();
}

MobileEntity::~MobileEntity() {
}

float MobileEntity::getMagnitude() const {
	return mag;
}

void MobileEntity::setMagnitude(float _mag) {
	mag = _mag;
}

Direction MobileEntity::getDirection() const {
	return dir;
}

void MobileEntity::setDirection(Direction _dir) {
	dir = _dir;
}

sf::Vector2f MobileEntity::getVector(const double& dt) const {
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

	vector.x = x_mag * (dt/1000000);
	vector.y = y_mag * (dt/1000000);
	return vector;
}

void MobileEntity::move(const double& dt) {
	sf::Vector2f vector = getVector(dt);

	geo.left = vector.x;
	geo.top = vector.y;
}

void MobileEntity::integrate(const double& dt) {
	sf::Vector2f vector = getVector(dt);
	
	state[0] = state[1];
	
	state[1].x += vector.x;
	state[1].y += vector.y;
}

void MobileEntity::interpolate(const double& alpha) {
	geo.left = state[1].x * alpha + state[0].x * (1. - alpha);
	geo.top = state[1].y * alpha + state[0].y * (1. - alpha);
}

bool MobileEntity::detectCollision(const Entity &entity) {
	return geo.intersects(entity.getGeo());
}

void MobileEntity::setPosition(const sf::Vector2f& pos) {
	Entity::setPosition(pos);
	state[0] = state[1] = pos;
}

void MobileEntity::setPosition(float x, float y) {
	Entity::setPosition(x,y);
	state[0] = state[1] = sf::Vector2f(x,y);
}

void MobileEntity::setGeo(const sf::FloatRect& _geo) {
	Entity::setGeo(_geo);
	state[0] = state[1] = sf::Vector2f(_geo.left,_geo.top);
}

void MobileEntity::setGeo(float x, float y, float w, float h) {
	Entity::setGeo(x,y,w,h);
	state[0] = state[1] = sf::Vector2f(x,y);
}