#include "EventManager.hpp"

#include <iostream>
#include <algorithm>

namespace gs {

EventManager::~EventManager() {
	std::cout << __FILE__ << " destroyed" << std::endl;
}

bool EventManager::addListener(EventEnum eventType, IEventListenerShPtr listener) {
bool EventManager::addListener(EventEnum eventType, IEventListenerPtr listener) {
	bool success = false;

	// TODO: Check for double registering (weak_ptrs dont have operator==)
	EventListenerList& listenerList = listeners[eventType];
	//EventListenerList::iterator it = std::find(listenerList.begin(),
		//listenerList.end(), listener);

	// if (it == listenerList.end()) {
	listenerList.push_back(listener);
	// 	success = true;
	// 	// TODO: Log success, listener added
	// } else {
	// 	// TODO: Log failure, attempting to double register listener
	// }

	return success;
}

bool EventManager::fireEvent(Event& event) {
	bool success = false;

	EventListenerMap::iterator mapIt = listeners.find(event.getType());
	if (mapIt != listeners.end()) {
		EventListenerList& listenerList = mapIt->second;

		if (!listenerList.empty()) {
			for (EventListenerList::iterator listIt = listenerList.begin();
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
