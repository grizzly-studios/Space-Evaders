#include "View.hpp"

#include <iostream>

namespace gs {

View::View(IEventManagerPtr _eventManager) : eventManager(_eventManager) {
	
}

View::~View() {
	std::cout << __FILE__ << " destroyed" << std::endl;
}

void View::update() {

}

void View::render() {

}

void View::onEvent(Event& event) {
	std::cout << "View: event: " << EventEnumToString(event.getType()) << std::endl;
}

}
