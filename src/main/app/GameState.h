/* 
 * File:   GameState.h
 * Author: williampoynter
 *
 * Created on October 25, 2013, 10:05 PM
 */

#ifndef GAMESTATE_H
#define	GAMESTATE_H

namespace gs {

enum GameState {
	IN_GAME,  //0
	PAUSED,   //1
	LOADING,  //2
	MENU,     //3
	INTRO,    //4
	GAMEOVER, //5
	GAMEWON   //6
};

}

#endif	/* GAMESTATE_H */

