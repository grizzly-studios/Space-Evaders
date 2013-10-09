#ifndef LOGIC_H
#define	LOGIC_H

#include <iostream>

#include "ILogic.hpp"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"

namespace gs {

class Logic : public ILogic, public IEventListener  {
public:
	Logic(IEventManagerPtr _eventManager);
	~Logic();
	virtual void update();
	virtual void onEvent(Event& event);
private:
	IEventManagerPtr eventManager;
};

}

#endif	/* LOGIC_H */
