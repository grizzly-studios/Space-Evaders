/* 
 * File:   IKeyboardListener.h
 * Author: williampoynter
 *
 * Created on October 13, 2013, 9:58 AM
 */

#ifndef I_KEYBOARDLISTENER_H
#define	I_KEYBOARDLISTENER_H

#include <memory>

namespace gs {
	
class IKeyboardListener {
public:
	virtual void update() = 0;
};

typedef std::shared_ptr<IKeyboardListener> IKeyboardListenerShrPtr;
	
}

#endif	/* I_KEYBOARDLISTENER_H */

