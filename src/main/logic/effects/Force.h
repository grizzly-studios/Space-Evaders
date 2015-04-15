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
	long int remaining;
	sf::Vector2f force;
public:
	Force(T* _obj, long int duration, sf::Vector2f _force) :
		obj(_obj),
		force(_force){
		remaining = duration;
		obj->effectForce = obj->effectForce + force;
	}
	virtual ~Force() {
		obj->effectForce = obj->effectForce - force;
	}

	bool hasExpired() {
		return remaining < 0;
	}
	void operator() (const long int &deltaTime) {
		remaining -= deltaTime;
	}
};

template<class T>
IEffectShPtr newForceShPtr(T* obj, long int duration, sf::Vector2f force) {
	return IEffectShPtr(new Force<T>(obj, duration, force));
}

} /* namespace gs */

#endif /* FORCE_H_ */
