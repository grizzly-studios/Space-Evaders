#ifndef ENTITY_CREATED_EVENT_H
#define	ENTITY_CREATED_EVENT_H

#include <SFML/Graphics/Rect.hpp>

#include "Event.hpp"

namespace gs {

class EntityCreatedEvent : public IEvent {
public:
	EntityCreatedEvent(short _entityId, const sf::FloatRect& _geo) : entityId(_entityId), geo(_geo)
	{}

	virtual EventEnum getType() const {
		return ENTITY_CREATED_EVENT;
	}

	short getEntityId() const {
		return entityId;
	}

	sf::FloatRect getGeo() const {
		return geo;
	}

private:
	short entityId;
	sf::FloatRect geo;
};

}

#endif	/* ENTITY_CREATED_EVENT_H */
