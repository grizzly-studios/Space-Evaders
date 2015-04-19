/* 
 * File:   GameWonScreen.h
 * Author: Al Lambert
 *
 * Created on April 18 2015 11:50
 */

#ifndef GAMEWONSCREEN_H
#define	GAMEWONSCREEN_H

#include "IGameWonScreen.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../../StyleManager.h"


namespace gs {

class GameWonScreen : public IGameWonScreen {
public:
	GameWonScreen(IStyleManagerShPtr);
	virtual ~GameWonScreen();
	
	void update();
	void render(RenderWindowShPtr);
	void setScore(int newScore);
	
	virtual ScreensEnum getType() const;
	
private:
	IStyleManagerShPtr styleManager;
};

}

#endif	/* GAMEWONSCREEN_H */

