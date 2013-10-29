#include "View.h"

#include <iostream>

#include "../util/Logger.h"

#define SPRITE_SHEET "assets/sprites.png"
#define SPRITE_SHEET_SPRITE_WIDTH 16
#define SCREEN_SPRITE_WIDTH 16

using namespace gs;

View::View(IEventManagerPtr _eventManager, 
	RenderWindowShPtr _window,
	IUserInputShPtr _userInput) : eventManager(_eventManager),
	window(_window),
	userInput(_userInput) {
}

View::~View() {
	DBG("Destroyed");
}

void View::init() {
	if (!texture.loadFromFile(SPRITE_SHEET)) {
		ERR("Failed to load texture: " + std::string(SPRITE_SHEET));
	}
}

void View::update() {
	userInput->update();
}

void View::render() {
	window->clear();

	for (SpriteMap::const_iterator it = spriteMap.begin(); it != spriteMap.end(); ++it) {
		window->draw(*(it->second));
	}

	window->display();
}

void View::onEvent(Event& event) {
	const short eventType = event.getType();
	INFO("Received event: " + eventType);

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

void View::onEntityCreated(EntityCreatedEvent& event) {
	const short entityId = event.getEntityId();
	INFO("Entity created with id: " + entityId);

	// Check if we already have a sprite associated with this id
	if (spriteMap.find(entityId) != spriteMap.end()) {
		WARN("Sprite already present for this id, should it have been destroyed?");
	}

	SpriteShPtr sprite(new sf::Sprite);
	sprite->setPosition(event.getPosition());
	// Logic dimensions map to screen pixels 1:1
	sprite->setScale(event.getDimensions() / (float) SCREEN_SPRITE_WIDTH);
	sprite->setTexture(texture);
	sprite->setTextureRect(sf::IntRect(0, 0, SPRITE_SHEET_SPRITE_WIDTH, SPRITE_SHEET_SPRITE_WIDTH));

	spriteMap[event.getEntityId()] = sprite;
}

void View::onEntityMoved(EntityMovedEvent& event) {
	const short entityId = event.getEntityId();
	INFO("Entity moved with id: " + entityId);

	// Check we have a sprite associated with this id
	SpriteMap::iterator it = spriteMap.find(entityId);
	if (it != spriteMap.end()) {
		it->second->setPosition(event.getPosition());
	} else {
		WARN("No sprite for this id");
	}
}
