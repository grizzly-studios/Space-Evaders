/*
 * IEffect.h
 *
 *  Created on: 8 Apr 2015
 *      Author: Will Poynter
 */

#ifndef IEFFECT_H_
#define IEFFECT_H_

namespace gs {

template<class T>
class IEffect {
public:
	virtual ~IEffect();
	virtual bool hasExpired(double* gameTime)=0;
	virtual void operator() (T* obj, double* gameTime)=0;
};

template<typename T>
using IEffectShPtr = std::shared_ptr<IEffect<T> >;
template<typename T>
using IEffectList = std::list<IEffectShPtr<T> >;

template<class TT>
class cleaner {
	double *gameTime;
public:
	cleaner(double *_gameTime) : gameTime(_gameTime) {}
	bool operator() (const IEffectShPtr<TT>& value) {
		return value->hasExpired(gameTime);
	}
};

template <typename T>
inline void clean (IEffectList<T> list, double* gameTime) {
	list.remove_if(cleaner<T>(gameTime));
}

} /* namespace gs */

#endif /* IEFFECT_H_ */
