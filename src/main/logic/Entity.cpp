/* 
 * File:   Entity.cpp
 * Author: williampoynter
 * 
 * Created on October 3, 2013, 11:25 PM
 */

#include "Entity.h"

using namespace gs;

Entity::Entity() {
}

Entity::Entity(const Entity& orig) {
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

sf::Vector2f Entity::getPosition() {
        return position;
}