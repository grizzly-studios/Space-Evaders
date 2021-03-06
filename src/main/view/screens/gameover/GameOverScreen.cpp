/* 
 * File:   GameOverScreen.cpp
 * Author: Rob Parker
 * 
 * Created on April 05 2015 12:50
 */

#include "GameOverScreen.h"

#include <sstream>
#include <string>

#include "../../../event/ScoreChangedEvent.hpp"


using namespace gs;

GameOverScreen::GameOverScreen(IStyleManagerShPtr _styleManager) :
	styleManager(_styleManager), score(0)
{}

GameOverScreen::~GameOverScreen() {
}

void GameOverScreen::update() {
}

ScreensEnum GameOverScreen::getType() const {
	return GAMEOVER_SCREEN;
}

void GameOverScreen::render(RenderWindowShPtr window) {
	sf::Font font;
	font = styleManager->getFont();
	sf::Text text;
	sf::RectangleShape textBorder;
	textBorder.setFillColor(sf::Color::Black);
	text.setFont(font);
	text.setCharacterSize(72);
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);

	textBorder.setSize(sf::Vector2f(215, 65));
	textBorder.setPosition(125,115);
	text.setString("GAME");
	text.setPosition(125,100);	
	window->draw(textBorder);
	window->draw(text);

	textBorder.setPosition(133,180);
	textBorder.setSize(sf::Vector2f(210, 58));
	text.setString("OVER");
	text.setPosition(133,165);
	window->draw(textBorder);
	window->draw(text);

	std::stringstream scoreText;
	scoreText << "Score:  " << score;

	text.setCharacterSize(24);
	textBorder.setSize(sf::Vector2f(120, 22));
	textBorder.setPosition(180,285);
	text.setString(scoreText.str());
	text.setPosition(180,280);
	window->draw(textBorder);
	window->draw(text);

	text.setCharacterSize(24);
	textBorder.setSize(sf::Vector2f(245, 22));
	textBorder.setPosition(125,405);
	text.setString("Press Escape to End");
	text.setPosition(125,400);
	window->draw(textBorder);
	window->draw(text);
}

void GameOverScreen::onEvent(Event& event) {
	if (event.getType() == SCORE_CHANGED_EVENT) {
		ScoreChangedEvent& scoreChangedEvent = (ScoreChangedEvent&) event;
		score = scoreChangedEvent.getScore();
	}
}
