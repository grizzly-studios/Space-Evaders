/* 
 * File:   GameOverScreen.h
 * Author: Rob Parker
 *
 * Created on April 05 2015 12:50
 */

#ifndef GAMEOVERSCREEN_H
#define	GAMEOVERSCREEN_H

#include "IGameOverScreen.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../../StyleManager.h"
#include "../../../event/IEventListener.hpp"


namespace gs {

class GameOverScreen : public IGameOverScreen, public IEventListener {
public:
	GameOverScreen(IStyleManagerShPtr);
	virtual ~GameOverScreen();
	
	void update();
	void render(RenderWindowShPtr);
	void setScore(int newScore);
	
	virtual ScreensEnum getType() const;

	virtual void onEvent(Event& event);
	
private:
	IStyleManagerShPtr styleManager;

	int score;
};

}

#endif	/* GAMEOVERSCREEN_H */

