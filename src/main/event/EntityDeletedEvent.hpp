#ifndef ENTITY_DELETED_EVENT_HPP
#define	ENTITY_DELETED_EVENT_HPP

#include "Event.hpp"

namespace gs {

/**
 * Event representing the deletion of an entity.
 */
class EntityDeletedEvent : public Event {
public:
	/**
	 * Constructor
	 * @param _entityId Entity id
	 */
	EntityDeletedEvent(short _entityId) : entityId(_entityId)
	{}

	/**
	 * Get the event type
	 * @return Event type
	 */
	virtual EventEnum getType() const {
		return ENTITY_DELETED_EVENT;
	}

	/**
	 * Get the entity id
	 * @return Entity id
	 */
	short getEntityId() const {
		return entityId;
	}

private:
	/** Entity id */
	short entityId;
};

}

#endif	/* ENTITY_DELETED_EVENT_HPP */
