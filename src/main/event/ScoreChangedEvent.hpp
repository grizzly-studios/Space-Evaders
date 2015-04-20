#ifndef SCORE_CHANGED_EVENT_HPP
#define SCORE_CHANGED_EVENT_HPP

#include "Event.hpp"

namespace gs {

/**
 * Event representing the destruction of a player.
 */
class ScoreChangedEvent : public Event {
public:
	/**
	 * Constructor
	 * @param _score New score
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
	 * Get the new score
	 * @return score
	 */
	int getScore() const {
		return score;
	}

private:
	/** New score */
	int score;
};

}

#endif	/* SCORE_CHANGED_EVENT_HPP */
