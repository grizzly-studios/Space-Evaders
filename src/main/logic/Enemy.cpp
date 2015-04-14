/* 
 * File:   Enemy.cpp
 * Author: williampoynter
 * 
 * Created on October 5, 2013, 9:53 AM
 */

#include "Enemy.h"

using namespace gs;

std::list<EnemyShPtr> Enemy::all;

Enemy::Enemy() : Entity() {
	name = "Enemy";
}

Enemy::Enemy(const Enemy& orig) : Entity(orig) {
}

Enemy::~Enemy() {
}

EnemyShPtr Enemy::create() {
	all.push_back(EnemyShPtr(new Enemy()));
	Entity::all.push_back(all.back());
	return all.back();
}

void Enemy::destroy(unsigned int _ID) {
	all.remove_if(cleaner(_ID));
	Entity::all.remove_if(cleaner(_ID));
}

void Enemy::destroy() {
	destroy(getID());
}
