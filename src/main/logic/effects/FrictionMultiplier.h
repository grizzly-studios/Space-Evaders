/*
 * FrictionMultipler.h
 *
 *  Created on: 9 Apr 2015
 *      Author: Will Poynter
 */

#ifndef FRICTIONMULTIPLER_H_
#define FRICTIONMULTIPLER_H_

#include "IEffect.h"

namespace gs {

template<class T>
class FrictionMultiplier: public IEffect {
private:
	T* obj;
	double* gameTime;
	double expirey;
	bool first;
	bool expired;
	float multiplier;
public:
	FrictionMultiplier(T* _obj, double* _gameTime, long int duration, float _multiplier) :
		obj(_obj),
		gameTime(_gameTime),
		first(true),
		expired(false),
		multiplier(_multiplier){
		expirey = *_gameTime + duration;
	}
	virtual ~FrictionMultiplier() {}

	bool hasExpired() {
		return expired;
	}
	void operator() () {
		if (first) {
			obj->setFriction(obj->getFriction()*multiplier);
			first = false;
		}
		expired = expirey < *gameTime;
		if (expired) {
			obj->setFriction(obj->getFriction()/multiplier);
		}
	}
};

template<class T>
inline IEffectShPtr newFrictionMultiplierShPtr(T* obj, double* gameTime, long int duration, float multiplier) {
	return IEffectShPtr(new FrictionMultiplier<T>(obj, gameTime, duration, multiplier));
}

} /* namespace gs */

#endif /* FRICTIONMULTIPLER_H_ */
