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
	std::cout << "View: event: " << EventEnumToString(event.getType()) << std::endl;
}

}
