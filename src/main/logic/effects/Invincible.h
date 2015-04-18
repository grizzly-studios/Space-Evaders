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
	long int remaining;
public:
	Invincible(T* _obj, long int duration) :
		obj(_obj){
		remaining =  duration;
		obj->setInvincible(true);
	}
	virtual ~Invincible() {
		obj->setInvincible(false);
	}

	bool hasExpired() {
		return remaining < 0;
	}
	void operator() (const long int &deltaTime) {
		remaining -= deltaTime;
	}
};

template<class T>
inline IEffectShPtr newInvincibleShPtr(T* obj, long int duration) {
	return IEffectShPtr(new Invincible<T>(obj, duration));
}

} /* namespace gs */

#endif /* INVINCIBLE_H_ */
