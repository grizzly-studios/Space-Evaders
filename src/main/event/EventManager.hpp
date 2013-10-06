#ifndef EVENT_MANAGER_H
#define	EVENT_MANAGER_H

#include "IEventManager.hpp"

namespace gs {

class EventManager : public IEventManager {
public:
	virtual void update() {}
};

}

#endif	/* EVENT_MANAGER_H */
