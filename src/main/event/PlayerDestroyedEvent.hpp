#ifndef PLAYER_DESTROYED_EVENT_HPP
#define	PLAYER_DESTROYED_EVENT_HPP

#include "Event.hpp"

namespace gs {

/**
 * Event representing the destruction of a player.
 */
class PlayerDestroyedEvent : public Event {
public:
	/**
	 * Constructor
	 * @param _entityId Entity id
	 */
	PlayerDestroyedEvent(short _entityId) : entityId(_entityId)
	{}

	/**
	 * Get the event type
	 * @return Event type
	 */
	virtual EventEnum getType() const {
		return PLAYER_DESTROYED_EVENT;
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

#endif	/* PLAYER_DESTROYED_EVENT_HPP */
