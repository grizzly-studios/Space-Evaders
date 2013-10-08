#include "EventManager.hpp"

#include <iostream>
#include <algorithm>

namespace gs {

EventManager::~EventManager() {
	std::cout << __FILE__ << " destroyed" << std::endl;
}

bool EventManager::addListener(EventEnum eventType, IEventListenerShPtr listener) {
	bool success = false;
	// TODO: Check for NULL pointers (assert/log?)
	// TODO: Typedef a shared_ptr for IEventListener

	// Get the listeners associated with the given event type
	EventListenerList& listenerList = listeners[eventType];
	EventListenerList::iterator it;

	// Check the listener being added is not already registered
	for (it = listenerList.begin(); it != listenerList.end(); ++it) {
		if (it->lock() == listener.lock()) {
			// TODO: Log failure, attempting to double register listener
			break;
		}
	}

	if (it == listenerList.end()) {
		listenerList.push_back(listener);
		success = true;
		// TODO: Log success, listener added
	}

	return success;
}

bool EventManager::fireEvent(Event& event) const {
	bool success = false;
	// TODO: Check for NULL pointers (assert/log?)

	// Get the listeners associated with event type
	EventListenerMap::const_iterator mapIt = listeners.find(event.getType());
	if (mapIt != listeners.end()) {
		const EventListenerList& listenerList = mapIt->second;

		if (!listenerList.empty()) {
			// Execute each listener, passing the event
			for (EventListenerList::const_iterator listIt = listenerList.begin();
				listIt != listenerList.end(); ++listIt) {
				(*listIt).lock()->onEvent(event);
			}
			success = true;
			// TODO: Log success, listeners called
		}
	}

	if (!success) {
		// TODO: Log failure, no listeners for event type
	}

	return success;
}

}
