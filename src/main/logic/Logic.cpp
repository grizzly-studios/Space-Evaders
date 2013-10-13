#include "Logic.hpp"

namespace gs {

Logic::Logic(IEventManagerPtr _eventManager) : eventManager(_eventManager) {

}

Logic::~Logic() {
	std::cout << __FILE__ << " destroyed" << std::endl;
}

void Logic::update() {

}

void Logic::onEvent(Event& event) {
	std::cout << "Logic: event: " << event.getType() << std::endl;
}

}
