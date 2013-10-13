/* 
 * File:   KeyboardListener.h
 * Author: williampoynter
 *
 * Created on October 13, 2013, 9:55 AM
 */

#ifndef KEYBOARDLISTENER_H
#define	KEYBOARDLISTENER_H

#include "IKeyboardListener.h"

namespace gs {

class KeyboardListener : public IKeyboardListener {
public:
	KeyboardListener(IEventManagerPtr _eventManager);
	virtual ~KeyboardListener();
	
	virtual void update();
private:
	IEventManagerPtr eventManager;
};

}

#endif	/* KEYBOARDLISTENER_H */

