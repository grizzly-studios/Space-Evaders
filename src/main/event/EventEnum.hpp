#ifndef EVENT_ENUM_HPP
#define	EVENT_ENUM_HPP

namespace gs {

/**
 * Enum for the different event types.
 */
enum EventEnum {
	GAME_STATE_CHANGED_EVENT,
	ENTITY_MOVED_EVENT,
	ENTITY_CREATED_EVENT,
	CHANGE_PLAYER_DIRECTION_EVENT,
	MOVE_MENU_POINTER_EVENT,
	GAME_START_EVENT
};

extern const char* EventEnumText[];

}

#endif	/* EVENT_ENUM_HPP */
