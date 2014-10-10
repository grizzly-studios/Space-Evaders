/* 
 * File:   Credits.h
 * Author: williampoynter
 *
 * Created on October 9, 2014, 5:21 PM
 */

#ifndef CREDITS_H
#define	CREDITS_H

#include "ICredits.h"

namespace gs {

class Credits : public ICredits {
public:
	Credits();
	virtual ~Credits();
	
	virtual void render();
private:

};

}

#endif	/* CREDITS_H */

