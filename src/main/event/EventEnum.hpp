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
	MOVE_MENU_POINTER_EVENT,		//4
	GAME_START_EVENT,				//5
	MENU_SELECT_EVENT,				//6
	MENU_POINTER_CHANGE,			//7
	GAME_END_EVENT 					//8
};

}

#endif	/* EVENT_ENUM_HPP */
