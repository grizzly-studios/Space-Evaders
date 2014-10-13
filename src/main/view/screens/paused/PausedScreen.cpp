/* 
 * File:   PausedScreen.cpp
 * Author: williampoynter
 * 
 * Created on October 13, 2014, 18:08 AM
 */

#include "PausedScreen.h"

using namespace gs;

PausedScreen::PausedScreen() {
}

PausedScreen::PausedScreen(IStyleManagerShPtr _styleManager) :
	styleManager(_styleManager)
{}

PausedScreen::~PausedScreen() {
}

void PausedScreen::update() {
	
}

ScreensEnum PausedScreen::getType() const {
	return PAUSED_SCREEN;
}

void PausedScreen::render(RenderWindowShPtr window) {

}