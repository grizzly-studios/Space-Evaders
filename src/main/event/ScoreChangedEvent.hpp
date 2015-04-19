#ifndef SCORE_CHANGED_EVENT_HPP
#define	SCORE_CHANGED_EVENT_HPP

#include "Event.hpp"

namespace gs {

/**
 * Event representing the destruction of a player.
 */
class ScoreChangedEvent : public Event {
public:
	/**
	 * Constructor
	 * @param _entityId Entity id
	 */
	ScoreChangedEvent(int _score) : score(_score)
	{}

	/**
	 * Get the event type
	 * @return Event type
	 */
	virtual EventEnum getType() const {
		return SCORE_CHANGED_EVENT;
	}

	/**
	 * Get the entity id
	 * @return Entity id
	 */
	int getScore() const {
		return score;
	}

private:
	/** Screen score */
	int score;
};

}

#endif	/* SCORE_CHANGED_EVENT_HPP */
