/* 
 * File:   LoadingScreen.cpp
 * Author: Rob Parker
 * 
 * Created on October 13, 2014, 23:11 PM
 */

#include "IntroScreen.h"

 // TODO: Refactor (duplicate constants in application layer)
#define WIDTH 480
#define HEIGHT 640

using namespace gs;

IntroScreen::IntroScreen() {
}

IntroScreen::IntroScreen(IStyleManagerShPtr _styleManager, IEventManagerPtr _eventManager) :
	styleManager(_styleManager), eventManager(_eventManager)
{
	if(!logoSound.loadFromFile("assets/logoPLACEHOLDER.ogg")){
		ERR << "Unable to open assets/logoPLACEHOLDER.ogg" << std::endl;
	}

	if(!logoTex.loadFromFile("assets/logo.png")){
		ERR << "Unable to open assets/logo.png" << std::endl;
	} else {
		logoTex.setRepeated(false);		
	}

}

IntroScreen::~IntroScreen() {
}

void IntroScreen::update() {
}

ScreensEnum IntroScreen::getType() const {
	return INTRO_SCREEN;
}

void IntroScreen::render(RenderWindowShPtr window) {
	// OK first work out where we are in terms of rendering the intro
	sf::Sprite logo;
	int fade;
	if(introCycle > 255 && introCycle <= 319){
		fade = 255;
		if(logSound.getStatus() == sf::SoundSource::Status::Stopped){
			logSound.setBuffer(logoSound);
			logSound.play();
		}
	} else if(introCycle > 319){
		fade = 255 - (introCycle - 319);
		if(fade <= 0){
			/* change state to menu */
			GameStateChangedEvent gameStateChangedEvent(MENU);
			eventManager->fireEvent(gameStateChangedEvent);
			return;
		}
	} else {
		fade = introCycle;
	}

	logo.setColor(sf::Color(fade,fade,fade,fade));

	logo.setTexture(logoTex);
	logo.setOrigin(sf::Vector2f(logo.getGlobalBounds().width/2,logo.getGlobalBounds().height/2));
	logo.setPosition(WIDTH/2,HEIGHT/2);
	logo.scale(sf::Vector2f(1.5f, 1.5f));
	window->draw(logo);

	introCycle += 2;
}