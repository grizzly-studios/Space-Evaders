#ifndef I_EVENT_LISTENER_HPP
#define	I_EVENT_LISTENER_HPP

#include <tr1/memory>

#include "Event.hpp"

namespace gs {

/**
 * Event listener interface.
 *
 * Classes implementing this interface can subscribe to specific events using the EventManager.
 */
class IEventListener {
public:
	/**
	 * Callback function for handling events
	 * @param event Event to process
	 */
	virtual void onEvent(Event& event) = 0;
};

typedef std::tr1::weak_ptr<IEventListener> IEventListenerPtr;

}

#endif	/* I_EVENT_LISTENER_HPP */
