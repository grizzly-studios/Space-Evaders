#ifndef ENTITY_MOVED_EVENT_H
#define	ENTITY_MOVED_EVENT_H

#include <SFML/System/Vector2.hpp>

#include "Event.hpp"

namespace gs {

class EntityMovedEvent : public IEvent {
public:
	EntityMovedEvent(short _entityId, const sf::Vector2f& _position) : entityId(_entityId),
		position(_position) {}

	virtual EventEnum getType() const {
		return ENTITY_MOVED_EVENT;
	}

	short getEntityId() const {
		return entityId;
	}

	sf::Vector2f getPosition() const {
		return position;
	}

private:
	short entityId;
	sf::Vector2f position;
};

}

#endif	/* ENTITY_MOVED_EVENT_H */
