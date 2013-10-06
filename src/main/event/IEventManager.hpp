#ifndef I_EVENT_MANAGER_H
#define	I_EVENT_MANAGER_H

#include <tr1/memory>

namespace gs {

class IEventManager {
public:
	virtual void update() = 0;
};

typedef std::tr1::shared_ptr<IEventManager> IEventManagerPtr;

}

#endif	/* I_EVENT_MANAGER_H */
