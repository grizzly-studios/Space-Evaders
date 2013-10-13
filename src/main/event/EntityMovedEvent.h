#ifndef ENTITY_MOVED_EVENT_H
#define	ENTITY_MOVED_EVENT_H

#include "Event.hpp"

namespace gs {

class EntityMovedEvent : public Event {
public:
	EntityMovedEvent(short _entityId) : entityId(_entityId) {};
	virtual ~EntityMovedEvent() {};

	virtual EventEnum getType() {
		return ENTITY_MOVED_EVENT;
	}

	short getEntityId() const {
		return entityId;
	}

	void setEntityId(short _entityId) {
		entityId = _entityId;
	}

private:
	short entityId;
};

}

#endif	/* ENTITY_MOVED_EVENT_H */
