#ifndef CHEESE_EVENT_H
#define	CHEESE_EVENT_H

#include "Event.hpp"

namespace gs {

class CheeseEvent : public Event {
public:
	virtual EventEnum getType() {
		return CHEESE_EVENT;
	}
};

}

#endif	/* CHEESE_EVENT_H */
