#ifndef I_EVENT_MANAGER_HPP
#define	I_EVENT_MANAGER_HPP

#include <memory>

#include "EventEnum.hpp"
#include "IEventListener.hpp"

/**
 * Cast a shared pointer to an IEventListenerPtr. The shared pointer must be wrapping an object
 * that implements IEventListener, otherwise this will go horribly wrong...
 */
#define MAKE_EVENT_LISTENER(_lsnr_) std::dynamic_pointer_cast<IEventListener>(_lsnr_)

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
	virtual bool fireEvent(Event& event) = 0;
};

typedef std::shared_ptr<IEventManager> IEventManagerPtr;

}

#endif	/* I_EVENT_MANAGER_HPP */
