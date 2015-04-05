/* 
 * File:   CreditsScreen.cpp
 * Author: Will Poynter
 * 
 * Created on April 5, 2015, 11:44 AM
 */

#include "CreditsScreen.h"

#include <cmath>

#include <SFML/Graphics/Text.hpp>

using namespace gs;

CreditsScreen::CreditsScreen()
{}

CreditsScreen::CreditsScreen(IStyleManagerShPtr _styleManager) :
	styleManager(_styleManager)
{}

CreditsScreen::~CreditsScreen() {
}

void CreditsScreen::update() {
}

ScreensEnum CreditsScreen::getType() const {
	return CREDITS_SCREEN;
}

void CreditsScreen::render(RenderWindowShPtr window) {
	sf::Font font;
	font = styleManager->getFont();

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);

	text.setString("AL LAMBERT");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,218);
	window->draw(text);

	text.setString("CHRIS REEVE-MATES");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,268);
	window->draw(text);

	text.setString("ROB PARKER");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,318);
	window->draw(text);

	text.setString("WILL POYNTER");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,368);
	window->draw(text);
}
