#ifndef ENTITY_MOVED_EVENT_HPP
#define	ENTITY_MOVED_EVENT_HPP

#include <SFML/System/Vector2.hpp>

#include "Event.hpp"

namespace gs {

/**
 * Event representing movement of an entity.
 */
class EntityMovedEvent : public Event {
public:
	/**
	 * Constructor
	 * @param _entityId Entity id
	 * @param _position New entity position
	 */
	EntityMovedEvent(short _entityId, const sf::Vector2f& _position) : entityId(_entityId),
		position(_position) {}

	/**
	 * Get the event type
	 * @return Event type
	 */
	virtual EventEnum getType() const {
		return ENTITY_MOVED_EVENT;
	}

	/**
	 * Get the entity id
	 * @return Entity id
	 */
	short getEntityId() const {
		return entityId;
	}

	/**
	 * Get the entity position
	 * @return Entity position
	 */
	sf::Vector2f getPosition() const {
		return position;
	}

private:
	/** Entity id */
	short entityId;
	/** New position */
	sf::Vector2f position;
};

}

#endif	/* ENTITY_MOVED_EVENT_HPP */
