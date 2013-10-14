#ifndef I_EVENT_MANAGER_HPP
#define	I_EVENT_MANAGER_HPP

#include <tr1/memory>

#include "EventEnum.hpp"
#include "IEventListener.hpp"

namespace gs {

/**
 * Event manager interface.
 *
 * The event manager provides decoupled communication between subsystems. Classes implementing
 * the IEventListener interface can subscribe to events of a specified type.
 */
class IEventManager {
public:
	/**
	 * Register an event listener with the event manager
	 * @param eventType Type of event to associate with the listener
	 * @param listener The event listener to register
	 * @return True if registration was successful
	 */
	virtual bool addListener(EventEnum eventType, IEventListenerPtr listener) = 0;
	/**
	 * Fire an event, executing all listeners subscribed to the event type
	 * @param event Event to fire
	 * @return True if the event was successfully forwarded to its registered listeners
	 */
	virtual bool fireEvent(Event& event) const = 0;
};

typedef std::tr1::shared_ptr<IEventManager> IEventManagerPtr;

}

#endif	/* I_EVENT_MANAGER_HPP */
