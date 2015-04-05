/* 
 * File:   GameOverScreen.cpp
 * Author: Rob Parker
 * 
 * Created on April 05 2015 12:50
 */

#include "GameOverScreen.h"


using namespace gs;

GameOverScreen::GameOverScreen()
{}

GameOverScreen::GameOverScreen(IStyleManagerShPtr _styleManager, IEventManagerPtr _eventManager) :
	styleManager(_styleManager),
	eventManager(_eventManager)
{}

GameOverScreen::~GameOverScreen() {
}

void GameOverScreen::update() {
}

ScreensEnum GameOverScreen::getType() const {
	return GAMEOVER_SCREEN;
}

void GameOverScreen::render(RenderWindowShPtr window) {
	//Draw GameOver
}
