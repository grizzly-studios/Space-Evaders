/* 
 * File:   Entity.cpp
 * Author: williampoynter
 * 
 * Created on September 25, 2013, 10:20 PM
 */

#include "Entity.h"

Entity::Entity() {
}

Entity::Entity(const Entity& orig) {
        *texture = orig.getTexture();
        *sprite = orig.getSprite();
}

Entity::Entity(const sf::Texture& orig) {
        *texture = orig;
}
Entity::Entity(const sf::Sprite& orig) {
        *sprite = orig;
}

Entity::~Entity() {
}

sf::Sprite Entity::operator ()() const {
        return getSprite();
}

sf::Texture Entity::getTexture() const {
        return *texture;
}

sf::Sprite Entity::getSprite() const {
        return *sprite;
}

unsigned int Entity::getX() {
        return x;
}

unsigned int Entity::getY() {
        return y;
}

bool Entity::collision(const sf::Rect<float>& rectangle) {
        return sprite->getGlobalBounds().intersects(rectangle);
}