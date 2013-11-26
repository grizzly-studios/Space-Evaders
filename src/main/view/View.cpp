#include "View.h"

#include <random>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>

#include "../util/Logger.h"

#define SCREEN_SPRITE_WIDTH 32		// pixels
#define LEVEL_TEXT "LEVEL"
#define WAVE_TEXT  "WAVE"
#define SCORE_TEXT "SCORE"
#define MULTI_TEXT "MULTI"
#define TEXT_SIZE 16 				// pixels

using namespace gs;

namespace {

sf::Vector2f convertToScreenCoords(const sf::Vector2f& logicCoords) {
	// Add offset for the HUD border
	return sf::Vector2f(logicCoords.x + SCREEN_SPRITE_WIDTH, logicCoords.y + SCREEN_SPRITE_WIDTH);
}

}

View::View(IEventManagerPtr _eventManager, RenderWindowShPtr _window, IUserInputShPtr _userInput,
	ISpriteFactoryShPtr _sprite_factory)
	: eventManager(_eventManager), window(_window), userInput(_userInput),
	spriteFactory(_sprite_factory), width(0), height(0) {
	width = window->getSize().x;
	height = window->getSize().y;
}

View::~View() {
	DBG("Destroyed");
}

void View::init() {
	spriteFactory->init();
	initBackground();
	initHud();

	if (!hudFont.loadFromFile("assets/joystix_monospace.ttf")) {
		ERR("Failed to load HUD font");
	}

	const int upperTextY = SCREEN_SPRITE_WIDTH + 5;
	const int lowerTextY = height - 58;
	const int rightTextX = width - SCREEN_SPRITE_WIDTH*5;

	levelText.setFont(hudFont);
	levelText.setString(LEVEL_TEXT);
	levelText.setCharacterSize(TEXT_SIZE);
	levelText.setPosition(SCREEN_SPRITE_WIDTH, upperTextY);

	waveText.setFont(hudFont);
	waveText.setString(WAVE_TEXT);
	waveText.setCharacterSize(TEXT_SIZE);
	waveText.setPosition(rightTextX, upperTextY);

	scoreText.setFont(hudFont);
	scoreText.setString(SCORE_TEXT);
	scoreText.setCharacterSize(TEXT_SIZE);
	scoreText.setPosition(SCREEN_SPRITE_WIDTH, lowerTextY);

	multiText.setFont(hudFont);
	multiText.setString(MULTI_TEXT);
	multiText.setCharacterSize(TEXT_SIZE);
	multiText.setPosition(rightTextX, lowerTextY);
}

void View::update() {
	userInput->update();
}

void View::render() {
	window->clear();

	// Draw background
	for (RectShapeList::const_iterator it = stars.begin(); it != stars.end(); ++it) {
		window->draw(*it);
	}

	// Draw entity sprites
	for (SpriteMap::const_iterator it = spriteMap.begin(); it != spriteMap.end(); ++it) {
		window->draw(it->second);
	}

	// Draw HUD sprites
	for (SpriteList::const_iterator it = hudSprites.begin(); it != hudSprites.end();
			++it) {
		window->draw(*it);
	}

	window->draw(levelText);
	window->draw(waveText);
	window->draw(scoreText);
	window->draw(multiText);

	drawGrid();

	window->display();
}

void View::onEvent(Event& event) {
	const short eventType = event.getType();
	std::stringstream ss;
	ss << "Received event: " << eventType;
	INFO(ss.str());

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
	default: {
		WARN("Event wasn't handled");
		break;
	}
	}
}

void View::initBackground() {return;
	// 'Randomly' position some stars
	const int NUM_STARS = 80;
	const int STAR_WIDTH = 3;
	const int SEED = 48;

	std::mt19937 randomNumGen(SEED);
	std::uniform_int_distribution<int> distX(SCREEN_SPRITE_WIDTH, width - SCREEN_SPRITE_WIDTH);
	std::uniform_int_distribution<int> distY(SCREEN_SPRITE_WIDTH, height - SCREEN_SPRITE_WIDTH);
	std::function<int()> genX(std::bind(distX, randomNumGen));
	std::function<int()> genY(std::bind(distY, randomNumGen));

	for (int i=0; i<NUM_STARS; i++) {
		stars.push_back(sf::RectangleShape(sf::Vector2f(STAR_WIDTH, STAR_WIDTH)));
		stars.back().setPosition(genX(), genY());
	}
}

void View::initHud() {
	// Top-left
	hudSprites.push_back(spriteFactory->createSprite(0, 0));

	// Left
	hudSprites.push_back(spriteFactory->createSprite(0, 1));
	hudSprites.back().setPosition(0.0f, SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(1.0f,
			(height - SCREEN_SPRITE_WIDTH * 2) / SCREEN_SPRITE_WIDTH);

	// Bottom-left
	hudSprites.push_back(spriteFactory->createSprite(0, 2));
	hudSprites.back().setPosition(0.0f, height - SCREEN_SPRITE_WIDTH);

	// Bottom
	hudSprites.push_back(spriteFactory->createSprite(1, 2));
	hudSprites.back().setPosition(SCREEN_SPRITE_WIDTH,
			height - SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(
			(width - SCREEN_SPRITE_WIDTH * 2) / SCREEN_SPRITE_WIDTH, 1.0f);

	// Bottom-right
	hudSprites.push_back(spriteFactory->createSprite(2, 2));
	hudSprites.back().setPosition(width - SCREEN_SPRITE_WIDTH,
			height - SCREEN_SPRITE_WIDTH);

	// Right
	hudSprites.push_back(spriteFactory->createSprite(2, 1));
	hudSprites.back().setPosition(width - SCREEN_SPRITE_WIDTH,
			SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(1.0f,
			(height - SCREEN_SPRITE_WIDTH * 2) / SCREEN_SPRITE_WIDTH);

	// Top-right
	hudSprites.push_back(spriteFactory->createSprite(2, 0));
	hudSprites.back().setPosition(width - SCREEN_SPRITE_WIDTH, 0.0f);

	// Top
	hudSprites.push_back(spriteFactory->createSprite(1, 0));
	hudSprites.back().setPosition(SCREEN_SPRITE_WIDTH, 0.0f);
	hudSprites.back().setScale(
			(width - SCREEN_SPRITE_WIDTH * 2) / SCREEN_SPRITE_WIDTH, 1.0f);
}

void View::onEntityCreated(EntityCreatedEvent& event) {
	const short entityId = event.getEntityId();
	std::stringstream ss;
	ss << "Entity created with id: " << entityId;
	INFO(ss.str());

	// Check if we already have a sprite associated with this id
	if (spriteMap.find(entityId) != spriteMap.end()) {
		WARN("Sprite already present for this id, should it have been destroyed?");
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
	}

	sf::Sprite sprite = spriteFactory->createSprite(spriteCol, spriteRow);
	sprite.setPosition(convertToScreenCoords(event.getPosition()));
	// Logic dimensions map to screen pixels 1:1
	sprite.setScale(event.getDimensions() / (float) SCREEN_SPRITE_WIDTH);

	spriteMap[event.getEntityId()] = sprite;
}

void View::onEntityMoved(EntityMovedEvent& event) {
	const short entityId = event.getEntityId();
	std::stringstream ss;
	ss << "Entity moved with id: " << entityId;
	INFO(ss.str());

	// Check we have a sprite associated with this id
	SpriteMap::iterator it = spriteMap.find(entityId);
	if (it != spriteMap.end()) {
		it->second.setPosition(convertToScreenCoords(event.getPosition()));
	} else {
		WARN("No sprite for this id");
	}
}

void View::drawGrid() {
	int horizLines = (height / SCREEN_SPRITE_WIDTH) -1;
	int vertLines = (width / SCREEN_SPRITE_WIDTH) -1;
	int numVertices = horizLines * vertLines;

	sf::Vertex* vertices = new sf::Vertex[numVertices];

	int count = 0;

	for (int i=0; i<horizLines; i++) {
		vertices[count++] = sf::Vertex(sf::Vector2f(0, SCREEN_SPRITE_WIDTH + i*SCREEN_SPRITE_WIDTH));
		vertices[count++] = sf::Vertex(sf::Vector2f(width, SCREEN_SPRITE_WIDTH + i*SCREEN_SPRITE_WIDTH));
	}

	for (int i=0; i<vertLines; i++) {
		vertices[count++] = sf::Vertex(sf::Vector2f(SCREEN_SPRITE_WIDTH + i*SCREEN_SPRITE_WIDTH, 0));
		vertices[count++] = sf::Vertex(sf::Vector2f(SCREEN_SPRITE_WIDTH + i*SCREEN_SPRITE_WIDTH, height));
	}

	window->draw(vertices, numVertices, sf::Lines);

	delete[] vertices;
}
