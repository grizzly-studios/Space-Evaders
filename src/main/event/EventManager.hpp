#ifndef EVENT_MANAGER_H
#define	EVENT_MANAGER_H

#include <map>
#include <list>

#include "IEventManager.hpp"

namespace gs {

typedef std::list<IEventListenerPtr> EventListenerList;
typedef std::map<EventEnum, EventListenerList> EventListenerMap;

class EventManager : public IEventManager {
public:
	~EventManager();
	virtual bool addListener(EventEnum eventType, IEventListenerPtr listener);
	virtual bool fireEvent(IEvent& event) const;
private:
	/** Map of listeners */
	EventListenerMap listeners;
};

}

#endif	/* EVENT_MANAGER_H */
