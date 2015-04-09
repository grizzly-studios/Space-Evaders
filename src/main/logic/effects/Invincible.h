/*
 * Invincible.h
 *
 *  Created on: 9 Apr 2015
 *      Author: Will Poynter
 */

#ifndef INVINCIBLE_H_
#define INVINCIBLE_H_

#include "IEffect.h"

namespace gs {

template<class T>
class Invincible: public IEffect {
private:
	T* obj;
	double* gameTime;
	double expirey;
	bool first;
	bool expired;
public:
	Invincible(T* _obj, double* _gameTime, long int duration) :
		obj(_obj),
		gameTime(_gameTime),
		first(true),
		expired(false){
		expirey = *_gameTime + duration;
	}
	virtual ~Invincible() {}

	bool hasExpired() {
		return expired;
	}
	void operator() () {
		if (first) {
			obj->setInvincible(true);
			first = false;
		}
		expired = expirey < *gameTime;
		if (expired) {
			obj->setInvincible(false);
		}
	}
};

template<class T>
inline IEffectShPtr newInvincibleShPtr(T* obj, double* gameTime, long int duration) {
	return IEffectShPtr(new Invincible<T>(obj, gameTime, duration));
}

} /* namespace gs */

#endif /* INVINCIBLE_H_ */
