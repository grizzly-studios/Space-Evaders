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
	sf::Text text;
	text.setFont(styleManager->getFont());
	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);

	sf::RectangleShape textBorder;
	textBorder.setFillColor(sf::Color::Black);

	textBorder.setSize(sf::Vector2f(170, 22));
	textBorder.setOrigin(sf::Vector2f(textBorder.getGlobalBounds().width/2, 0));
	textBorder.setPosition(styleManager->getWidth()/2,222);
	text.setString("AL LAMBERT");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,218);
	window->draw(textBorder);
	window->draw(text);

	textBorder.setSize(sf::Vector2f(280, 22));
	textBorder.setOrigin(sf::Vector2f(textBorder.getGlobalBounds().width/2, 0));
	textBorder.setPosition(styleManager->getWidth()/2,272);
	text.setString("CHRIS REEVE-MATES");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,268);
	window->draw(textBorder);
	window->draw(text);

	textBorder.setSize(sf::Vector2f(180, 22));
	textBorder.setOrigin(sf::Vector2f(textBorder.getGlobalBounds().width/2, 0));
	textBorder.setPosition(styleManager->getWidth()/2,322);
	text.setString("ROB PARKER");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,318);
	window->draw(textBorder);
	window->draw(text);

	textBorder.setSize(sf::Vector2f(200, 22));
	textBorder.setOrigin(sf::Vector2f(textBorder.getGlobalBounds().width/2, 0));
	textBorder.setPosition(styleManager->getWidth()/2,372);
	text.setString("WILL POYNTER");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,368);
	window->draw(textBorder);
	window->draw(text);
}
