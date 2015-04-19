/* 
 * File:   ScreensEnum.h
 * Author: williampoynter
 *
 * Created on October 12, 2014, 2:51 PM
 */

#ifndef SCREENSENUM_H
#define	SCREENSENUM_H

namespace gs {

/**
 * Enum for the different screens.
 */
enum ScreensEnum {
	CREDITS_SCREEN,
	GAME_SCREEN,
	INTRO_SCREEN,
	LOADING_SCREEN,
	MENU_SCREEN,
	OPTIONS_SCREEN,
	PAUSED_SCREEN,
	GAMEOVER_SCREEN,
	GAMEWON_SCREEN
};

extern const char* ScreensEnumText[];

}

#endif	/* SCREENSENUM_H */

