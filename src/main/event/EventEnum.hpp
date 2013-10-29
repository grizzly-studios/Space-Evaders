#ifndef EVENT_ENUM_HPP
#define	EVENT_ENUM_HPP

#include <map>
#include <vector>
#include <string>

namespace gs {

/**
 * Enum for the different event types.
 */
enum EventEnum {
	GAME_STATE_CHANGED_EVENT,
	ENTITY_MOVED_EVENT,
	ENTITY_CREATED_EVENT,
	CHANGE_PLAYER_DIRECTION_EVENT
};

}

#endif	/* EVENT_ENUM_HPP */
