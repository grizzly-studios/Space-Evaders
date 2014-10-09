/* 
 * File:   ICredits.h
 * Author: williampoynter
 *
 * Created on October 9, 2014, 5:28 PM
 */

#ifndef ICREDITS_H
#define	ICREDITS_H

#include <memory>

namespace gs {
	
class ICredits {
public:
	virtual void update() = 0;
	virtual void render() = 0;
};

typedef std::shared_ptr<ICredits> ICreditsShPtr;
	
}

#endif	/* ICREDITS_H */

