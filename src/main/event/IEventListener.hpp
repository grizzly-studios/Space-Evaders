#ifndef I_EVENT_LISTENER_HPP
#define	I_EVENT_LISTENER_HPP

#include <tr1/memory>

#include "Event.hpp"

namespace gs {

class IEventListener {
public:
	virtual void onEvent(Event& event) = 0;
};

typedef std::tr1::weak_ptr<IEventListener> IEventListenerPtr;

}

#endif	/* I_EVENT_LISTENER_HPP */
