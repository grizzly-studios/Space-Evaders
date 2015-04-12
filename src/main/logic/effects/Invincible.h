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
public:
	Invincible(T* _obj, double* _gameTime, long int duration) :
		obj(_obj),
		gameTime(_gameTime){
		expirey = *_gameTime + duration;
		obj->setInvincible(true);
	}
	virtual ~Invincible() {
		obj->setInvincible(false);
	}

	bool hasExpired() {
		return expirey < *gameTime;
	}
	void operator() () {}
};

template<class T>
inline IEffectShPtr newInvincibleShPtr(T* obj, double* gameTime, long int duration) {
	return IEffectShPtr(new Invincible<T>(obj, gameTime, duration));
}

} /* namespace gs */

#endif /* INVINCIBLE_H_ */
