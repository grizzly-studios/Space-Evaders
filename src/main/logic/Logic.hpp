#ifndef LOGIC_H
#define	LOGIC_H

#include "ILogic.hpp"
#include "../event/IEventManager.hpp"

namespace gs {

class Logic : public ILogic {
public:
	Logic(IEventManagerPtr _eventManager) : eventManager(_eventManager) {}
	virtual void update() {}
private:
	IEventManagerPtr eventManager;
};

}

#endif	/* LOGIC_H */
