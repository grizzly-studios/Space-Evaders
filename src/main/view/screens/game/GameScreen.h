/* 
 * File:   GameScreen.h
 * Author: williampoynter
 *
 * Created on October 10, 2014, 5:14 PM
 */

#ifndef GAMESCREEN_H
#define	GAMESCREEN_H

#include "IGameScreen.h"

namespace gs {

class GameScreen :public IGameScreen {
public:
	GameScreen();
	virtual ~GameScreen();
	
	void update();
	void render(RenderWindowShPtr);
	
	virtual ScreensEnum getType() const;
private:

};

}

#endif	/* GAMESCREEN_H */

