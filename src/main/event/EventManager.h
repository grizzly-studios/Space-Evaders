#ifndef EVENT_MANAGER_H
#define	EVENT_MANAGER_H

#include <map>
#include <list>

#include "IEventManager.hpp"

namespace gs {

typedef std::list<IEventListenerPtr> EventListenerList;
typedef std::map<EventEnum, EventListenerList> EventListenerMap;

/**
 * Event manager implementation.
 *
 * The event manager provides decoupled communication between subsystems. Classes implementing
 * the IEventListener interface can subscribe to events of a specified type.
 */
class EventManager : public IEventManager {
public:
	/**
	 * Destructor
	 */
	~EventManager();
	/**
	 * Register an event listener with the event manager
	 * @param eventType Type of event to associate with the listener
	 * @param listener The event listener to register
	 * @return True if registration was successful
	 */
	virtual bool addListener(EventEnum eventType, IEventListenerPtr listener);
	/**
	 * Fire an event, executing all listeners subscribed to the event type
	 * @param event Event to fire
	 * @return True if the event was successfully forwarded to its registered listeners
	 */
	virtual bool fireEvent(Event& event);
private:
	/**
	 * Clear expired weak_ptrs from map
	 * @param eventType Type of event to associate with the listener
	 */
	void clearExpired(EventEnum eventType);
	/** Map of listeners */
	EventListenerMap listeners;
};

}

#endif	/* EVENT_MANAGER_H */
