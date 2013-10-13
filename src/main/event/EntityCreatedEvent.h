#ifndef ENTITY_CREATED_EVENT_H
#define	ENTITY_CREATED_EVENT_H

#include "Event.hpp"

namespace gs {

class EntityCreatedEvent : public Event {
public:
	EntityCreatedEvent(short _entityId) : entityId(_entityId) {};
	virtual ~EntityCreatedEvent() {};

	virtual EventEnum getType() {
		return ENTITY_CREATED_EVENT;
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

#endif	/* ENTITY_CREATED_EVENT_H */
