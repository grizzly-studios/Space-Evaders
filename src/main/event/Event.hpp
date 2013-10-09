#ifndef EVENT_H
#define	EVENT_H

#include "EventEnum.hpp"

namespace gs {

class Event {
public:
	virtual EventEnum getType() = 0;
};

}

#endif	/* EVENT_H */
