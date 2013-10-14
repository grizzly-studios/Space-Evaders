#ifndef ENTITY_CREATED_EVENT_HPP
#define	ENTITY_CREATED_EVENT_HPP

#include <SFML/Graphics/Rect.hpp>

#include "Event.hpp"

namespace gs {

class EntityCreatedEvent : public Event {
public:
	EntityCreatedEvent(short _entityId, const sf::FloatRect& _geo) : entityId(_entityId), geo(_geo)
	{}

	virtual EventEnum getType() const {
		return ENTITY_CREATED_EVENT;
	}

	short getEntityId() const {
		return entityId;
	}

	sf::Vector2f getPosition() const {
		return sf::Vector2f(geo.left, geo.top);
	}

	sf::Vector2f getDimensions() const {
		return sf::Vector2f(geo.width, geo.height);
	}

private:
	short entityId;
	sf::FloatRect geo;
};

}

#endif	/* ENTITY_CREATED_EVENT_HPP */
