/* 
 * File:   Entity.cpp
 * Author: williampoynter
 * 
 * Created on October 3, 2013, 11:25 PM
 */

#include "Entity.h"

using namespace gs;

unsigned int Entity::counter = 0;
std::list<EntityShPtr> Entity::all;
std::list<EntityShPtr> Entity::toRemove;

Entity::Entity() {
	geo.left = 0;
	geo.top = 0;
	geo.width = 0;
	geo.height = 0;
	counter++;
	ID = counter;
}

Entity::Entity(const Entity& orig) {
	geo = orig.getGeo();
	name = orig.getName();
	counter++;
	ID = counter;
}

Entity::~Entity() {
}

EntityShPtr Entity::create() {
	all.push_back(EntityShPtr(new Entity()));
	return all.back();
}

void Entity::destroy(unsigned int _ID) {
	all.remove_if(cleaner(_ID));
}

void Entity::destroy() {
	destroy(getID());
}

void Entity::clean() {
	while(!toRemove.empty()) {
		toRemove.front()->destroy();
		toRemove.pop_front();
	}
}

void Entity::setPosition(const sf::Vector2f &pos) {
	geo.left = pos.x;
	geo.top = pos.y;
}

void Entity::setPosition(float x, float y) {
	geo.left = x;
	geo.top = y;
}

sf::Vector2f Entity::getPosition() const {
	return sf::Vector2f(geo.left,geo.top);
}

void Entity::setDimensions(const sf::Vector2f &dim) {
	geo.width = dim.x;
	geo.height = dim.y;
}

void Entity::setDimensions(float w, float h) {
	geo.width = w;
	geo.height = h;
}

sf::Vector2f Entity::getDimensions() const {
	return sf::Vector2f(geo.width,geo.height);
}

void Entity::setGeo(const sf::FloatRect& _geo) {
	geo = _geo;
}

void Entity::setGeo(float x, float y, float w, float h) {
	geo.left = x;
	geo.top = y;
	geo.width = w;
	geo.height = h;
}

sf::FloatRect Entity::getGeo() const {
	return geo;
}

void Entity::setName(const std::string& _name) {
	name = _name;
}

std::string Entity::getName() const {
	return name;
}

unsigned int Entity::getID() const {
	return ID;
}
