#ifndef EVENT_HPP
#define	EVENT_HPP

#include "EventEnum.hpp"
#include "../util/Logger.h"

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
	friend std::ostream & operator<<(std::ostream &logger, const Event& event)
	{
		return logger << EventEnumText[event.getType()];
	}
};

}

#endif	/* EVENT_HPP */
