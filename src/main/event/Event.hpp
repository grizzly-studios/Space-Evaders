#ifndef EVENT_HPP
#define	EVENT_HPP

#include "EventEnum.hpp"

namespace gs {

class Event {
public:
	virtual EventEnum getType() const = 0;
};

}

#endif	/* EVENT_HPP */
