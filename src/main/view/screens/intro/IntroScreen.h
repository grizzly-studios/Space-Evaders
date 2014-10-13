/* 
 * File:   IntroScreen.h
 * Author: Rob Parker
 *
 * Created on October 13, 2014, 23:11 PM
 */

#ifndef INTROSCREEN_H
#define	INTROSCREEN_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include "IIntroScreen.h"

#include "../../../util/Logger.h"
#include "../../StyleManager.h"

#include "../../../app/GameState.h"
#include "../../../event/GameStateChangedEvent.h"
#include "../../../event/IEventManager.hpp"


namespace gs {

class IntroScreen : public IIntroScreen {
public:
	IntroScreen();
	IntroScreen(IStyleManagerShPtr, IEventManagerPtr);
	virtual ~IntroScreen();
	
	void update();
	void render(RenderWindowShPtr);
	
	virtual ScreensEnum getType() const;
	
private:
	IStyleManagerShPtr styleManager;
	IEventManagerPtr eventManager;

	sf::Texture* p_logoTex;
	int introCycle;
	sf::Texture logoTex;
	sf::Image logoImg;
	sf::SoundBuffer logoSound;
	sf::Sound logSound;
};

}

#endif	/* INTROSCREEN_H */

