/*
 * IEffect.h
 *
 *  Created on: 8 Apr 2015
 *      Author: Will Poynter
 */

#ifndef IEFFECT_H_
#define IEFFECT_H_

namespace gs {

class IEffect {
public:
	virtual ~IEffect() {}
	virtual bool hasExpired()=0;
	virtual void operator() (const long int &deltaTime)=0;
};

typedef std::shared_ptr<IEffect> IEffectShPtr;
typedef std::list<IEffectShPtr> IEffectList;

inline void clean (IEffectList &list) {
	class cleaner {
	public:
		cleaner() {}
		bool operator() (const IEffectShPtr& value) {
			return value->hasExpired();
		}
	};
	list.remove_if(cleaner());
}

} /* namespace gs */

#endif /* IEFFECT_H_ */
