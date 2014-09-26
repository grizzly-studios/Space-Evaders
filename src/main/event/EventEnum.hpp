#ifndef EVENT_ENUM_HPP
#define	EVENT_ENUM_HPP

namespace gs {

/**
 * Enum for the different event types.
 */
enum EventEnum {
	GAME_STATE_CHANGED_EVENT, 		//0
	ENTITY_MOVED_EVENT,       		//1
	ENTITY_CREATED_EVENT,     		//2
	CHANGE_PLAYER_DIRECTION_EVENT,	//3
	GAME_START_EVENT,				//4
	MENU_SELECT_EVENT,				//5
	MENU_POINTER_CHANGE,			//6
	GAME_END_EVENT, 				//7
	MENU_ACTION_EVENT				//8
};

extern const char* EventEnumText[];

}

#endif	/* EVENT_ENUM_HPP */
