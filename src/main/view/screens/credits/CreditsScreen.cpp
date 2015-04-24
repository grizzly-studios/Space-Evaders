/* 
 * File:   CreditsScreen.cpp
 * Author: Will Poynter
 * 
 * Created on April 5, 2015, 11:44 AM
 */

#include "CreditsScreen.h"

#include <cmath>

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

	logo.setTexture(logoTex);
	logo.setOrigin(sf::Vector2f(logo.getGlobalBounds().width/2,logo.getGlobalBounds().height/2));
	logo.setPosition(GBL::WIDTH/2,logo.getGlobalBounds().height);
	logo.scale(sf::Vector2f(1.0f, 1.0f));

	sf::Text genericNameText;
	genericNameText.setFont(styleManager->getFont());
	genericNameText.setCharacterSize(24);
	genericNameText.setColor(sf::Color::Red);
	genericNameText.setStyle(sf::Text::Bold);
	sf::Text genericTitleText;
	genericTitleText.setFont(styleManager->getFont());
	genericTitleText.setCharacterSize(20);
	genericTitleText.setColor(sf::Color::White);
	genericTitleText.setStyle(sf::Text::Underlined);
	sf::RectangleShape genericNameBorder;
	genericNameBorder.setFillColor(sf::Color::Black);
	sf::RectangleShape genericTitleBorder;
	genericTitleBorder.setFillColor(sf::Color::Black);

	titleBorders.push_back(sf::RectangleShape(genericTitleBorder));
	titleBorders.back().setSize(sf::Vector2f(330, 22));
	titleBorders.back().setOrigin(sf::Vector2f(titleBorders.back().getGlobalBounds().width/2, 0));
	titleBorders.back().setPosition(styleManager->getWidth()/2,222);
	titleTexts.push_back(sf::Text(genericTitleText));
	titleTexts.back().setString("Development & Deployment Director");
	titleTexts.back().setOrigin(sf::Vector2f(titleTexts.back().getGlobalBounds().width/2,0));
	titleTexts.back().setPosition(styleManager->getWidth()/2,218);

	nameBorders.push_back(sf::RectangleShape(genericNameBorder));
	nameBorders.back().setSize(sf::Vector2f(170, 22));
	nameBorders.back().setOrigin(sf::Vector2f(nameBorders.back().getGlobalBounds().width/2, 0));
	nameBorders.back().setPosition(styleManager->getWidth()/2,245);
	nameTexts.push_back(sf::Text(genericNameText));
	nameTexts.back().setString("AL LAMBERT");
	nameTexts.back().setOrigin(sf::Vector2f(nameTexts.back().getGlobalBounds().width/2,0));
	nameTexts.back().setPosition(styleManager->getWidth()/2,241);

	titleBorders.push_back(sf::RectangleShape(genericTitleBorder));
	titleBorders.back().setSize(sf::Vector2f(170, 22));
	titleBorders.back().setOrigin(sf::Vector2f(titleBorders.back().getGlobalBounds().width/2, 0));
	titleBorders.back().setPosition(styleManager->getWidth()/2,297);
	titleTexts.push_back(sf::Text(genericTitleText));
	titleTexts.back().setString("Creative Director");
	titleTexts.back().setOrigin(sf::Vector2f(titleTexts.back().getGlobalBounds().width/2,0));
	titleTexts.back().setPosition(styleManager->getWidth()/2,295);

	nameBorders.push_back(sf::RectangleShape(genericNameBorder));
	nameBorders.back().setSize(sf::Vector2f(280, 22));
	nameBorders.back().setOrigin(sf::Vector2f(nameBorders.back().getGlobalBounds().width/2, 0));
	nameBorders.back().setPosition(styleManager->getWidth()/2,320);
	nameTexts.push_back(sf::Text(genericNameText));
	nameTexts.back().setString("CHRIS REEVE-MATES");
	nameTexts.back().setOrigin(sf::Vector2f(nameTexts.back().getGlobalBounds().width/2,0));
	nameTexts.back().setPosition(styleManager->getWidth()/2,318);

	titleBorders.push_back(sf::RectangleShape(genericTitleBorder));
	titleBorders.back().setSize(sf::Vector2f(190, 22));
	titleBorders.back().setOrigin(sf::Vector2f(titleBorders.back().getGlobalBounds().width/2, 0));
	titleBorders.back().setPosition(styleManager->getWidth()/2,372);
	titleTexts.push_back(sf::Text(genericTitleText));
	titleTexts.back().setString("Operations Director");
	titleTexts.back().setOrigin(sf::Vector2f(titleTexts.back().getGlobalBounds().width/2,0));
	titleTexts.back().setPosition(styleManager->getWidth()/2,368);

	nameBorders.push_back(sf::RectangleShape(genericNameBorder));
	nameBorders.back().setSize(sf::Vector2f(180, 22));
	nameBorders.back().setOrigin(sf::Vector2f(nameBorders.back().getGlobalBounds().width/2, 0));
	nameBorders.back().setPosition(styleManager->getWidth()/2,395);
	nameTexts.push_back(sf::Text(genericNameText));
	nameTexts.back().setString("ROB PARKER");
	nameTexts.back().setOrigin(sf::Vector2f(nameTexts.back().getGlobalBounds().width/2,0));
	nameTexts.back().setPosition(styleManager->getWidth()/2,391);

	titleBorders.push_back(sf::RectangleShape(genericTitleBorder));
	titleBorders.back().setSize(sf::Vector2f(190, 22));
	titleBorders.back().setOrigin(sf::Vector2f(titleBorders.back().getGlobalBounds().width/2, 0));
	titleBorders.back().setPosition(styleManager->getWidth()/2,447);
	titleTexts.push_back(sf::Text(genericTitleText));
	titleTexts.back().setString("Managing Director");
	titleTexts.back().setOrigin(sf::Vector2f(titleTexts.back().getGlobalBounds().width/2,0));
	titleTexts.back().setPosition(styleManager->getWidth()/2,445);

	nameBorders.push_back(sf::RectangleShape(genericNameBorder));
	nameBorders.back().setSize(sf::Vector2f(200, 22));
	nameBorders.back().setOrigin(sf::Vector2f(nameBorders.back().getGlobalBounds().width/2, 0));
	nameBorders.back().setPosition(styleManager->getWidth()/2,470);
	nameTexts.push_back(sf::Text(genericNameText));
	nameTexts.back().setString("WILL POYNTER");
	nameTexts.back().setOrigin(sf::Vector2f(nameTexts.back().getGlobalBounds().width/2,0));
	nameTexts.back().setPosition(styleManager->getWidth()/2,468);
}

CreditsScreen::~CreditsScreen() {
}

void CreditsScreen::update() {
}

ScreensEnum CreditsScreen::getType() const {
	return CREDITS_SCREEN;
}

void CreditsScreen::render(RenderWindowShPtr window) {

	window->draw(logo);

	for (sf::RectangleShape& nameBorder: nameBorders) {
		window->draw(nameBorder);
	}
	for (sf::RectangleShape& titleBorder: titleBorders) {
		window->draw(titleBorder);
	}
	for (sf::Text& nameText: nameTexts) {
		window->draw(nameText);
	}
	for (sf::Text& titleText: titleTexts) {
		window->draw(titleText);
	}
}








