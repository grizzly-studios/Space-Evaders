/* 
 * File:   IUserInput.h
 * Author: williampoynter
 *
 * Created on October 13, 2013, 9:27 AM
 */

#ifndef I_USERINPUT_H
#define	I_USERINPUT_H

#include <tr1/memory>

namespace gs {
	
class IUserInput {
public:
	virtual void update() = 0;
};

typedef std::tr1::shared_ptr<IUserInput> IUserInputShPtr;
	
}

#endif	/* I_USERINPUT_H */

