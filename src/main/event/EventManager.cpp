#include "EventManager.h"

#include <iostream>
#include <algorithm>

#include "../util/Logger.h"

using namespace gs;

EventManager::~EventManager() {
	DBG << "Destroyed" << std::endl;
}

bool EventManager::addListener(EventEnum eventType, IEventListenerPtr listener) {
	bool success = false;
	// TODO: Check for NULL pointers (assert/log?)
	// TODO: Typedef a shared_ptr for IEventListener

	// Get the listeners associated with the given event type
	EventListenerList& listenerList = listeners[eventType];
	EventListenerList::iterator it;

	// Check the listener being added is not already registered
	for (it = listenerList.begin(); it != listenerList.end(); ++it) {
		if (it->lock() == listener.lock()) {
			WARN << "Failed to add listener as listener was already registered" << std::endl;
			break;
		}
	}

	if (it == listenerList.end()) {
		listenerList.push_back(listener);
		success = true;
		INFO << "Successfully added listener" << std::endl;
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
				listIt->lock()->onEvent(event);
			}
			success = true;
		}
	}

	if (!success) {
		WARN << "Failed to fire event as there were no listeners for the event type" << std::endl;
	}

	return success;
}
