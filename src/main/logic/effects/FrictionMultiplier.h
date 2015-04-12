/*
 * FrictionMultipler.h
 *
 *  Created on: 9 Apr 2015
 *      Author: Will Poynter
 */

#ifndef FRICTIONMULTIPLER_H_
#define FRICTIONMULTIPLER_H_

#include "IEffect.h"

#include <iostream>

namespace gs {

template<class T>
class FrictionMultiplier: public IEffect {
private:
	T* obj;
	double* gameTime;
	double expirey;
	float multiplier;
public:
	FrictionMultiplier(T* _obj, double* _gameTime, long int duration, float _multiplier) :
		obj(_obj),
		gameTime(_gameTime),
		multiplier(_multiplier){
		expirey = *_gameTime + duration;
		obj->setFriction(obj->getFriction()*multiplier);
	}
	virtual ~FrictionMultiplier() {
		obj->setFriction(obj->getFriction()/multiplier);
	}

	bool hasExpired() {
		return expirey < *gameTime;
	}
	void operator() () {}
};

template<class T>
IEffectShPtr newFrictionMultiplierShPtr(T* obj, double* gameTime, long int duration, float multiplier) {
	return IEffectShPtr(new FrictionMultiplier<T>(obj, gameTime, duration, multiplier));
}

} /* namespace gs */

#endif /* FRICTIONMULTIPLER_H_ */
