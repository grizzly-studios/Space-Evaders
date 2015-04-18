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

#include "../../../util/Logger.h"
#include "../../StyleManager.h"

#include "../../../app/GameState.h"
#include "../../../event/GameStateChangedEvent.h"
#include "../../../event/IEventManager.hpp"


namespace gs {

class GameOverScreen : public IGameOverScreen {
public:
	GameOverScreen(IStyleManagerShPtr, IEventManagerPtr);
	virtual ~GameOverScreen();
	
	void update();
	void render(RenderWindowShPtr);
	void setScore(int newScore);
	
	virtual ScreensEnum getType() const;
	
private:
	IStyleManagerShPtr styleManager;
	IEventManagerPtr eventManager;
};

}

#endif	/* GAMEOVERSCREEN_H */

