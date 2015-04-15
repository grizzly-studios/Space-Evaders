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
	long int remaining;
	float multiplier;
public:
	FrictionMultiplier(T* _obj, long int duration, float _multiplier) :
		obj(_obj),
		multiplier(_multiplier){
		remaining = duration;
		obj->setFriction(obj->getFriction()*multiplier);
	}
	virtual ~FrictionMultiplier() {
		obj->setFriction(obj->getFriction()/multiplier);
	}

	bool hasExpired() {
		return remaining < 0;
	}
	void operator() (const long int &deltaTime) {
		remaining -= deltaTime;
	}
};

template<class T>
IEffectShPtr newFrictionMultiplierShPtr(T* obj, long int duration, float multiplier) {
	return IEffectShPtr(new FrictionMultiplier<T>(obj, duration, multiplier));
}

} /* namespace gs */

#endif /* FRICTIONMULTIPLER_H_ */
