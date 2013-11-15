#ifndef ENTITY_CREATED_EVENT_HPP
#define	ENTITY_CREATED_EVENT_HPP

#include <SFML/Graphics/Rect.hpp>

#include "Event.hpp"
#include "../logic/EntityEnum.hpp"

namespace gs {

/**
 * Event representing the creation of an entity.
 */
class EntityCreatedEvent : public Event {
public:
	/**
	 * Constructor
	 * @param _entityId Entity id
	 * @param _entityType Entity type
	 * @param _geo Rectangle representing the entity position and dimensions
	 */
	EntityCreatedEvent(short _entityId, EntityEnum _entityType, const sf::FloatRect& _geo)
		: entityId(_entityId), entityType(_entityType), geo(_geo) {
	}

	/**
	 * Get the event type
	 * @return Event type
	 */
	virtual EventEnum getType() const {
		return ENTITY_CREATED_EVENT;
	}

	/**
	 * Get the entity id
	 * @return Entity id
	 */
	short getEntityId() const {
		return entityId;
	}

	/**
	 * Get the entity type
	 * @return the Entity type
	 */
	EntityEnum getEntityType() const {
		return entityType;
	}


	/**
	 * Get the entity position
	 * @return Entity position
	 */
	sf::Vector2f getPosition() const {
		return sf::Vector2f(geo.left, geo.top);
	}

	/**
	 * Get the entity dimensions
	 * @return Entity dimensions
	 */
	sf::Vector2f getDimensions() const {
		return sf::Vector2f(geo.width, geo.height);
	}

private:
	/** Entity id */
	short entityId;
	/** Entity type */
	EntityEnum entityType;
	/** Position and dimensions of the entity */
	sf::FloatRect geo;
};

}

#endif	/* ENTITY_CREATED_EVENT_HPP */
