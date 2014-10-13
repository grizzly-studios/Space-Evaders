/* 
 * File:   LoadingScreen.cpp
 * Author: williampoynter
 * 
 * Created on October 13, 2014, 09:29 PM
 */

#include "LoadingScreen.h"

using namespace gs;

LoadingScreen::LoadingScreen() {
}

LoadingScreen::LoadingScreen(IStyleManagerShPtr _styleManager) :
	styleManager(_styleManager)
{}

LoadingScreen::~LoadingScreen() {
}

void LoadingScreen::update() {
	
}

ScreensEnum LoadingScreen::getType() const {
	return LOADING_SCREEN;
}

void LoadingScreen::render(RenderWindowShPtr window) {
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
	text.setString("LOADING");
	text.setPosition(137,252);
	window->draw(textBorder);
	window->draw(text);
}