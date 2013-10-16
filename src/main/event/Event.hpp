#ifndef EVENT_HPP
#define	EVENT_HPP

#include "EventEnum.hpp"

namespace gs {


/**
 * Base class for events.
 */
class Event {
public:
	/**
	 * Get the event type
	 * @return Event type
	 */
	virtual EventEnum getType() const = 0;
};

}

#endif	/* EVENT_HPP */
