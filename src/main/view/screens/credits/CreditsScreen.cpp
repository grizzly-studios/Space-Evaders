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
{
	if(!logoTex.loadFromFile(styleManager->getAssetPath("logo.png"))){
		ERR << "Unable to open assets/logo.png" << std::endl;
	} else {
		logoTex.setRepeated(false);		
	}
}

CreditsScreen::~CreditsScreen() {
}

void CreditsScreen::update() {
}

ScreensEnum CreditsScreen::getType() const {
	return CREDITS_SCREEN;
}

void CreditsScreen::render(RenderWindowShPtr window) {
	sf::Sprite logo;

	logo.setTexture(logoTex);
	logo.setOrigin(sf::Vector2f(logo.getGlobalBounds().width/2,logo.getGlobalBounds().height/2));
	logo.setPosition(GBL::WIDTH/2,logo.getGlobalBounds().height);
	logo.scale(sf::Vector2f(1.0f, 1.0f));
	window->draw(logo);

	sf::Font font;
	font = styleManager->getFont();

	sf::Text nameText;
	nameText.setFont(font);
	nameText.setCharacterSize(24);
	nameText.setColor(sf::Color::Red);
	nameText.setStyle(sf::Text::Bold);

	sf::Text titleText;
	titleText.setFont(font);
	titleText.setCharacterSize(20);
	titleText.setColor(sf::Color::White);
	titleText.setStyle(sf::Text::Underlined);


	sf::RectangleShape nameBorder;
	nameBorder.setFillColor(sf::Color::Black);

	sf::RectangleShape titleBorder;
	titleBorder.setFillColor(sf::Color::Black);

	titleBorder.setSize(sf::Vector2f(330, 22));
	titleBorder.setOrigin(sf::Vector2f(titleBorder.getGlobalBounds().width/2, 0));
	titleBorder.setPosition(styleManager->getWidth()/2,222);
	titleText.setString("Development & Deployment Director");
	titleText.setOrigin(sf::Vector2f(titleText.getGlobalBounds().width/2,0));
	titleText.setPosition(styleManager->getWidth()/2,218);
	window->draw(titleBorder);
	window->draw(titleText);


	nameBorder.setSize(sf::Vector2f(170, 22));
	nameBorder.setOrigin(sf::Vector2f(nameBorder.getGlobalBounds().width/2, 0));
	nameBorder.setPosition(styleManager->getWidth()/2,245);
	nameText.setString("AL LAMBERT");
	nameText.setOrigin(sf::Vector2f(nameText.getGlobalBounds().width/2,0));
	nameText.setPosition(styleManager->getWidth()/2,241);
	window->draw(nameBorder);
	window->draw(nameText);

	titleBorder.setSize(sf::Vector2f(170, 22));
	titleBorder.setOrigin(sf::Vector2f(titleBorder.getGlobalBounds().width/2, 0));
	titleBorder.setPosition(styleManager->getWidth()/2,297);
	titleText.setString("Creative Director");
	titleText.setOrigin(sf::Vector2f(titleText.getGlobalBounds().width/2,0));
	titleText.setPosition(styleManager->getWidth()/2,295);
	window->draw(titleBorder);
	window->draw(titleText);


	nameBorder.setSize(sf::Vector2f(280, 22));
	nameBorder.setOrigin(sf::Vector2f(nameBorder.getGlobalBounds().width/2, 0));
	nameBorder.setPosition(styleManager->getWidth()/2,320);
	nameText.setString("CHRIS REEVE-MATES");
	nameText.setOrigin(sf::Vector2f(nameText.getGlobalBounds().width/2,0));
	nameText.setPosition(styleManager->getWidth()/2,318);
	window->draw(nameBorder);
	window->draw(nameText);

	titleBorder.setSize(sf::Vector2f(190, 22));
	titleBorder.setOrigin(sf::Vector2f(titleBorder.getGlobalBounds().width/2, 0));
	titleBorder.setPosition(styleManager->getWidth()/2,372);
	titleText.setString("Operations Director");
	titleText.setOrigin(sf::Vector2f(titleText.getGlobalBounds().width/2,0));
	titleText.setPosition(styleManager->getWidth()/2,368);
	window->draw(titleBorder);
	window->draw(titleText);

	nameBorder.setSize(sf::Vector2f(180, 22));
	nameBorder.setOrigin(sf::Vector2f(nameBorder.getGlobalBounds().width/2, 0));
	nameBorder.setPosition(styleManager->getWidth()/2,395);
	nameText.setString("ROB PARKER");
	nameText.setOrigin(sf::Vector2f(nameText.getGlobalBounds().width/2,0));
	nameText.setPosition(styleManager->getWidth()/2,391);
	window->draw(nameBorder);
	window->draw(nameText);

	titleBorder.setSize(sf::Vector2f(190, 22));
	titleBorder.setOrigin(sf::Vector2f(titleBorder.getGlobalBounds().width/2, 0));
	titleBorder.setPosition(styleManager->getWidth()/2,447);
	titleText.setString("Managing Director");
	titleText.setOrigin(sf::Vector2f(titleText.getGlobalBounds().width/2,0));
	titleText.setPosition(styleManager->getWidth()/2,445);
	window->draw(titleBorder);
	window->draw(titleText);

	nameBorder.setSize(sf::Vector2f(200, 22));
	nameBorder.setOrigin(sf::Vector2f(nameBorder.getGlobalBounds().width/2, 0));
	nameBorder.setPosition(styleManager->getWidth()/2,470);
	nameText.setString("WILL POYNTER");
	nameText.setOrigin(sf::Vector2f(nameText.getGlobalBounds().width/2,0));
	nameText.setPosition(styleManager->getWidth()/2,468);
	window->draw(nameBorder);
	window->draw(nameText);
}








