/*
 * Flashing.h
 *
 *  Created on: 9 Apr 2015
 *      Author: Will Poynter
 */

#ifndef FLASHING_H_
#define FLASHING_H_

#include "IEffect.h"

namespace gs {

template<class T>
class Flashing: public IEffect {
private:
	T* obj;
	double* gameTime;
	double expirey;
	bool first;
	bool expired;
	float multiplier;
	long int period;
	double nextSwitch;
public:
	Flashing(T* _obj, double* _gameTime, long int duration, float _multiplier, long int _period) :
		obj(_obj),
		gameTime(_gameTime),
		first(true),
		expired(false),
		multiplier(_multiplier),
		period(_period) {
		expirey = *_gameTime + duration;
	}
	virtual ~Flashing() {}

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
inline IEffectShPtr newFlashingShPtr(T* obj, double* gameTime, long int duration, float multiplier, long int period) {
	return IEffectShPtr(new Flashing<T>(obj, gameTime, duration, multiplier, period));
}

} /* namespace gs */

#endif /* FRICTIONMULTIPLER_H_ */
