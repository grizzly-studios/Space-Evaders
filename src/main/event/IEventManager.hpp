#ifndef I_EVENT_MANAGER_H
#define	I_EVENT_MANAGER_H

#include <tr1/memory>

#include "EventEnum.hpp"
#include "IEventListener.hpp"

namespace gs {

class IEventManager {
public:
	virtual bool addListener(EventEnum eventType, IEventListenerPtr listener) = 0;
	virtual bool fireEvent(IEvent& event) const = 0;
};

typedef std::tr1::shared_ptr<IEventManager> IEventManagerPtr;

}

#endif	/* I_EVENT_MANAGER_H */
