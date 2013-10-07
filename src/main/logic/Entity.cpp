/* 
 * File:   Entity.cpp
 * Author: williampoynter
 * 
 * Created on October 3, 2013, 11:25 PM
 */

#include "Entity.h"

using namespace gs;

int Entity::counter = 0;

Entity::Entity() {
    position.x = 0;
    position.y = 0;
	counter++;
	ID = counter;
}

Entity::Entity(const Entity& orig) {
    position = orig.getPosition();
    *skin = orig.getSkin();
    name = orig.getName();
	counter++;
	ID = counter;
}

Entity::~Entity() {
}

void Entity::setPosition(const sf::Vector2f &pos) {
	position = pos;
}

void Entity::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

sf::Vector2f Entity::getPosition() const {
	return position;
}

void Entity::setDimensions(const sf::Vector2f &dim) {
	dimensions = dim;
}

void Entity::setDimensions(float w, float h) {
	dimensions.x = w;
	dimensions.y = h;
}

sf::Vector2f Entity::getDimensions() const {
	return dimensions;
}

void Entity::setSkin(const Skin &_skin) {
    *skin = _skin;
}

Skin Entity::getSkin() const {
    return *skin;
}

void Entity::setName(const std::string& _name) {
    name = _name;
}

std::string Entity::getName() const {
    return name;
}