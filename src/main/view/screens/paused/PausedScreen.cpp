/* 
 * File:   PausedScreen.cpp
 * Author: williampoynter
 * 
 * Created on October 13, 2014, 06:08 PM
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
	//Don't know why this bit is needed ---
	sf::Font font;
	font = styleManager->getFont();
	// --- Don't know why this bit is needed 
	sf::Text text;
	sf::RectangleShape textBorder;
	textBorder.setFillColor(sf::Color::Black);
	text.setFont(font);
	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);

	textBorder.setSize(sf::Vector2f(120, 22));
	textBorder.setPosition(135,256);
	text.setString("PAUSED");
	text.setPosition(137,252);
	window->draw(textBorder);
	window->draw(text);

	textBorder.setSize(sf::Vector2f(200, 22));
	textBorder.setPosition(135,290);
	text.setString("P to Continue");
	text.setPosition(137,286);
	window->draw(textBorder);
	window->draw(text);
	
	
	textBorder.setPosition(135,324);
	text.setString("Escape to Quit");
	text.setPosition(137,320);
	window->draw(textBorder);
	window->draw(text);
}