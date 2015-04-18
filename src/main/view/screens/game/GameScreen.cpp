/* 
 * File:   GameScreen.cpp
 * Author: williampoynter
 * 
 * Created on October 10, 2014, 5:14 PM
 */

#include "GameScreen.h"

#include "../../../app/Globals.h"

using namespace gs;

GameScreen::GameScreen(
		IStyleManagerShPtr _styleManager,
		ISpriteFactoryShPtr _spriteFactory) :
	styleManager(_styleManager),
	spriteFactory(_spriteFactory) {
	spriteFactory->init();

	const int upperTextY = GBL::SCREEN_SPRITE_WIDTH + 5;
	const int lowerTextY = styleManager->getHeight() - 58;
	const int rightTextX = styleManager->getWidth() - GBL::SCREEN_SPRITE_WIDTH*5;

	short int textSize = 16; 		//pixels

	levelText.setFont(styleManager->getFont(StyleGroup::HUD));
	levelText.setString("LEVEL");
	levelText.setCharacterSize(textSize);
	levelText.setPosition(GBL::SCREEN_SPRITE_WIDTH, upperTextY);

	waveText.setFont(styleManager->getFont(StyleGroup::HUD));
	waveText.setString("WAVE");
	waveText.setCharacterSize(textSize);
	waveText.setPosition(rightTextX, upperTextY);

	scoreText.setFont(styleManager->getFont(StyleGroup::HUD));
	scoreText.setString("SCORE");
	scoreText.setCharacterSize(textSize);
	scoreText.setPosition(GBL::SCREEN_SPRITE_WIDTH, lowerTextY);

	multiText.setFont(styleManager->getFont(StyleGroup::HUD));
	multiText.setString("MULTI");
	multiText.setCharacterSize(textSize);
	multiText.setPosition(rightTextX, lowerTextY);

	initHud();
}

GameScreen::~GameScreen() {
}

void GameScreen::update() {
	
}

ScreensEnum GameScreen::getType() const {
	return GAME_SCREEN;
}

void GameScreen::render(RenderWindowShPtr window) {
	// Draw entity sprites (GAME)
	for (SpriteMap::const_iterator it = spriteMap.begin(); it != spriteMap.end(); ++it) {
		window->draw(it->second);
	}

	// Draw HUD sprites (GAME)
	for (SpriteList::const_iterator it = hudSprites.begin(); it != hudSprites.end();
			++it) {
		window->draw(*it);
	}

	window->draw(levelText);
	window->draw(waveText);
	window->draw(scoreText);
	window->draw(multiText);

	drawGrid(window);

	window->display();
}

void GameScreen::onEvent(Event& event) {
	const short eventType = event.getType();
	INFO << "Received event: " << event << std::endl;

	switch (eventType) {
		case ENTITY_CREATED_EVENT: {
			EntityCreatedEvent& entityCreatedEvent = (EntityCreatedEvent&) event;
			onEntityCreated(entityCreatedEvent);
			break;
		}
		case ENTITY_MOVED_EVENT: {
			EntityMovedEvent& entityMovedEvent = (EntityMovedEvent&) event;
			onEntityMoved(entityMovedEvent);
			break;
		}
		case ENTITY_DELETED_EVENT: {
			EntityDeletedEvent& entityDeletedEvent = (EntityDeletedEvent&) event;
			onEntityDeleted(entityDeletedEvent);
			break;
		}
		case GAME_END_EVENT: {
			onGameEnd();
			break;
		}
		default: {
		    ERR << "Un-Handled: " << event << std::endl;
			break;
		}
	}
}

void GameScreen::onEntityCreated(EntityCreatedEvent& event) {
	const short entityId = event.getEntityId();
	INFO << "Entity created with id: " << entityId << std::endl;

	// Check if we already have a sprite associated with this id
	if (spriteMap.find(entityId) != spriteMap.end()) {
		WARN << "Sprite already present for this id, should it have been destroyed?" << std::endl;
	}

	int spriteCol = -1;
	int spriteRow = -1;
	switch (event.getEntityType()) {
		case PLAYER_ENTITY:
			spriteCol = 3;
			spriteRow = 0;
			break;
		case ENEMY_ENTITY:
			spriteCol = 3;
			spriteRow = 1;
			break;
		case BULLET_ENTITY:
			spriteCol = 3;
			spriteRow = 2;
			break;
	}

	sf::Sprite sprite = spriteFactory->createSprite(spriteCol, spriteRow,
			(sf::Vector2i)event.getDimensions());
	sprite.setPosition(event.getPosition());
	// Logic dimensions map to screen pixels 1:1
	//sprite.setScale(event.getDimensions() / (float) GBL::SCREEN_SPRITE_WIDTH);

	spriteMap[event.getEntityId()] = sprite;
}

void GameScreen::onEntityDeleted(EntityDeletedEvent& event) {
	const short entityId = event.getEntityId();


	// Check if we already have a sprite associated with this id
	if (spriteMap.find(entityId) == spriteMap.end()) {
		WARN << "Sprite  with ID "<< entityId << " has already been destroyed" << std::endl;
		return;
	}

	INFO << "Entity deleted with id: " << entityId << std::endl;

	spriteMap.erase(event.getEntityId());
}

void GameScreen::onEntityMoved(EntityMovedEvent& event) {
	const short entityId = event.getEntityId();
	INFO << "Entity moved with id: " << entityId << std::endl;

	// Check we have a sprite associated with this id
	SpriteMap::iterator it = spriteMap.find(entityId);
	if (it != spriteMap.end()) {
		it->second.setPosition(event.getPosition());
	} else {
		WARN << "No sprite for this id" << std::endl;
	}
}

void GameScreen::onGameEnd(){
	spriteMap.clear();
}

void GameScreen::initHud() {
	// Top-left
	hudSprites.push_back(spriteFactory->createSprite(0, 0));

	// Left
	hudSprites.push_back(spriteFactory->createSprite(0, 1));
	hudSprites.back().setPosition(0.0f, GBL::SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(1.0f,
			(GBL::HEIGHT - GBL::SCREEN_SPRITE_WIDTH * 2) / GBL::SCREEN_SPRITE_WIDTH);

	// Bottom-left
	hudSprites.push_back(spriteFactory->createSprite(0, 2));
	hudSprites.back().setPosition(0.0f, GBL::HEIGHT - GBL::SCREEN_SPRITE_WIDTH);

	// Bottom
	hudSprites.push_back(spriteFactory->createSprite(1, 2));
	hudSprites.back().setPosition(GBL::SCREEN_SPRITE_WIDTH,
			GBL::HEIGHT - GBL::SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(
			(GBL::WIDTH - GBL::SCREEN_SPRITE_WIDTH * 2) / GBL::SCREEN_SPRITE_WIDTH, 1.0f);

	// Bottom-right
	hudSprites.push_back(spriteFactory->createSprite(2, 2));
	hudSprites.back().setPosition(GBL::WIDTH - GBL::SCREEN_SPRITE_WIDTH,
			GBL::HEIGHT - GBL::SCREEN_SPRITE_WIDTH);

	// Right
	hudSprites.push_back(spriteFactory->createSprite(2, 1));
	hudSprites.back().setPosition(GBL::WIDTH - GBL::SCREEN_SPRITE_WIDTH,
			GBL::SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(1.0f,
			(GBL::HEIGHT - GBL::SCREEN_SPRITE_WIDTH * 2) / GBL::SCREEN_SPRITE_WIDTH);

	// Top-right
	hudSprites.push_back(spriteFactory->createSprite(2, 0));
	hudSprites.back().setPosition(GBL::WIDTH - GBL::SCREEN_SPRITE_WIDTH, 0.0f);

	// Top
	hudSprites.push_back(spriteFactory->createSprite(1, 0));
	hudSprites.back().setPosition(GBL::SCREEN_SPRITE_WIDTH, 0.0f);
	hudSprites.back().setScale(
			(GBL::WIDTH - GBL::SCREEN_SPRITE_WIDTH * 2) / GBL::SCREEN_SPRITE_WIDTH, 1.0f);
}

void GameScreen::drawGrid(RenderWindowShPtr window) {
	int horizLines = (styleManager->getHeight() / GBL::SCREEN_SPRITE_WIDTH) -1;
	int vertLines = (styleManager->getWidth() / GBL::SCREEN_SPRITE_WIDTH) -1;
	int numVertices = horizLines * vertLines;

	sf::Vertex* vertices = new sf::Vertex[numVertices];

	int count = 0;

	for (int i=0; i<horizLines; i++) {
		vertices[count++] = sf::Vertex(sf::Vector2f(0, GBL::SCREEN_SPRITE_WIDTH + i*GBL::SCREEN_SPRITE_WIDTH));
		vertices[count++] = sf::Vertex(sf::Vector2f(styleManager->getWidth(), GBL::SCREEN_SPRITE_WIDTH + i*GBL::SCREEN_SPRITE_WIDTH));
	}

	for (int i=0; i<vertLines; i++) {
		vertices[count++] = sf::Vertex(sf::Vector2f(GBL::SCREEN_SPRITE_WIDTH + i*GBL::SCREEN_SPRITE_WIDTH, 0));
		vertices[count++] = sf::Vertex(sf::Vector2f(GBL::SCREEN_SPRITE_WIDTH + i*GBL::SCREEN_SPRITE_WIDTH, styleManager->getHeight()));
	}

	window->draw(vertices, numVertices, sf::Lines);

	delete[] vertices;
}
