#ifndef I_EVENT_LISTENER_H
#define	I_EVENT_LISTENER_H

#include <tr1/memory>

#include "Event.hpp"

namespace gs {

class IEventListener {
public:
	virtual void onEvent(Event& event) = 0;
};

typedef std::tr1::weak_ptr<IEventListener> IEventListenerShPtr;

}

#endif	/* I_EVENT_LISTENER_H */
