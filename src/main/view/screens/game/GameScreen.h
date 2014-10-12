/* 
 * File:   GameScreen.h
 * Author: williampoynter
 *
 * Created on October 10, 2014, 5:14 PM
 */

#ifndef GAMESCREEN_H
#define	GAMESCREEN_H

#include "../../IScreen.h"

namespace gs {

class GameScreen :public IScreen {
public:
	GameScreen();
	virtual ~GameScreen();
	
	void update();
	void render(RenderWindowShPtr);
private:

};

}

#endif	/* GAMESCREEN_H */

