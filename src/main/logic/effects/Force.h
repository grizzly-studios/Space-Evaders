/*
 * Force.h
 *
 *  Created on: 14 Apr 2015
 *      Author: Will Poynter
 */

#ifndef FORCE_H_
#define FORCE_H_

#include "IEffect.h"

#include <iostream>

namespace gs {

template<class T>
class Force: public IEffect {
private:
	T* obj;
	double* gameTime;
	double expirey;
	sf::Vector2f force;
public:
	Force(T* _obj, double* _gameTime, long int duration, sf::Vector2f _force) :
		obj(_obj),
		gameTime(_gameTime),
		force(_force){
		expirey = *_gameTime + duration;
		obj->effectForce = obj->effectForce + force;
	}
	virtual ~Force() {
		obj->effectForce = obj->effectForce - force;
	}

	bool hasExpired() {
		return expirey < *gameTime;
	}
	void operator() () {}
};

template<class T>
IEffectShPtr newForceShPtr(T* obj, double* gameTime, long int duration, sf::Vector2f force) {
	return IEffectShPtr(new Force<T>(obj, gameTime, duration, force));
}

} /* namespace gs */

#endif /* FORCE_H_ */
