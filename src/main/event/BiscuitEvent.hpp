#ifndef BISCUIT_EVENT_H
#define	BISCUIT_EVENT_H

#include "Event.hpp"

namespace gs {

class BiscuitEvent : public Event {
public:
	virtual EventEnum getType() {
		return BISCUIT_EVENT;
	}
};

}

#endif	/* BISCUIT_EVENT_H */
