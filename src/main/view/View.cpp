#include "View.hpp"

#include <iostream>

namespace gs {

View::View(IEventManagerPtr _eventManager, RenderWindowShPtr _window) : eventManager(_eventManager),
	window(_window) {

}

View::~View() {
	std::cout << __FILE__ << " destroyed" << std::endl;
}

void View::update() {

}

void View::render() {
	window->clear();

	for (SpriteMap::const_iterator it = spriteMap.begin(); it != spriteMap.end(); ++it) {
		window->draw(*it->second);
	}

	window->display();
}

void View::onEvent(Event& event) {
	std::cout << "View: event: ";

	switch (event.getType()) {
	case ENTITY_CREATED_EVENT: {
		std::cout << "ENTITY_CREATED_EVENT" << std::endl;
		EntityCreatedEvent& entityCreatedEvent = (EntityCreatedEvent&) event;
		onEntityCreated(entityCreatedEvent);
		break;
	}
	case ENTITY_MOVED_EVENT: {
		std::cout << "ENTITY_MOVED_EVENT" << std::endl;
		EntityMovedEvent& entityMovedEvent = (EntityMovedEvent&) event;
		onEntityMoved(entityMovedEvent);
		break;
	}
	default: {
		std::cout << "<UNHANDLED EVENT>" << std::endl;
		break;
	}
	}
}

void View::onEntityCreated(EntityCreatedEvent& event) {
	std::cout << "entity created with id: " << event.getEntityId() << std::endl;

	SpriteShPtr sprite(new sf::Sprite);
	sprite->setTexture(texture);
	sprite->setTextureRect(sf::IntRect(0, 0, SPRITE_WIDTH, SPRITE_WIDTH));
	spriteMap[event.getEntityId()] = sprite;
}

void View::onEntityMoved(EntityMovedEvent& event) {
	std::cout << "entity moved with id: " << event.getEntityId() << std::endl;
}

}
