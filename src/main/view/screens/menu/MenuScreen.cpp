/* 
 * File:   MenuScreen.cpp
 * Author: williampoynter
 * 
 * Created on October 12, 2014, 9:00 AM
 */

#include "MenuScreen.h"

using namespace gs;

MenuScreen::MenuScreen() {
}

MenuScreen::MenuScreen(IStyleManagerShPtr _styleManager) :
	styleManager(_styleManager),
	menuPos(0)
{}

MenuScreen::~MenuScreen() {
}

void MenuScreen::update() {
	
}

void MenuScreen::setMenuPos(int _menuPos) {
	menuPos = _menuPos;
}

void MenuScreen::moveMenuPos(int movement) {
	int intrimMenuPos = menuPos;
	intrimMenuPos = intrimMenuPos - movement;
	intrimMenuPos = intrimMenuPos % 4;
	if (intrimMenuPos < 0){
		intrimMenuPos = intrimMenuPos + 4;
	}
	menuPos = intrimMenuPos;
	DBG << "New menu position: " << menuPos << std::endl;
}

int MenuScreen::getMenuPos() {
	return menuPos;
}

void MenuScreen::setSelected(MenuItem _selected) {
	selected = _selected;
}

MenuItem MenuScreen::getSelected() {
	return selected;
}

ScreensEnum MenuScreen::getType() const {
	return MENU_SCREEN;
}

void MenuScreen::render(RenderWindowShPtr window) {
	sf::Text text;
	sf::RectangleShape textBorder;
	textBorder.setFillColor(sf::Color::Black);
	text.setFont(styleManager->getFont());
	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	
	textBorder.setSize(sf::Vector2f(200, 22));
	textBorder.setOrigin(sf::Vector2f(textBorder.getGlobalBounds().width/2, 0));
	textBorder.setPosition(styleManager->getWidth()/2,222);
	text.setString("START EVADING");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,218);
	if (menuPos == 0 ) {
		text.setColor(sf::Color::White);
	} else {
		text.setColor(sf::Color::Red);
	}
	window->draw(textBorder);
	window->draw(text);
	
	textBorder.setSize(sf::Vector2f(120, 22));
	textBorder.setOrigin(sf::Vector2f(textBorder.getGlobalBounds().width/2, 0));
	textBorder.setPosition(styleManager->getWidth()/2,256);
	text.setString("OPTIONS");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,252);
	if (menuPos == 1 ) {
		text.setColor(sf::Color::White);
	} else {
		text.setColor(sf::Color::Red);
	}
	window->draw(textBorder);
	window->draw(text);
	
	textBorder.setPosition(styleManager->getWidth()/2,290);
	text.setString("CREDITS");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,286);
	if (menuPos == 2 ) {
		text.setColor(sf::Color::White);
	} else {
		text.setColor(sf::Color::Red);
	}
	window->draw(textBorder);
	window->draw(text);
	
	textBorder.setSize(sf::Vector2f(64, 22));
	textBorder.setOrigin(sf::Vector2f(textBorder.getGlobalBounds().width/2, 0));
	textBorder.setPosition(styleManager->getWidth()/2,324);
	text.setString("QUIT");
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2,0));
	text.setPosition(styleManager->getWidth()/2,320);
	if (menuPos == 3 ) {
		text.setColor(sf::Color::White);
	} else {
		text.setColor(sf::Color::Red);
	}
	window->draw(textBorder);
	window->draw(text);
}
