#include "Logic.h"

#include "../util/Logger.h"
#include <sstream>

using namespace gs;

Logic::Logic(IEventManagerPtr _eventManager, RenderWindowShPtr _window) : eventManager(_eventManager),window(_window) {
	clock = new sf::Clock();
	accumulator = 0;
	dt = 12500;
	currentMenuPos = 0;
}

Logic::~Logic() {
	DBG << "Destroyed" << std::endl;
}

void Logic::update() {
	sf::Time elapsed = clock->restart();
	double interval = elapsed.asMicroseconds();
	if (interval > 250000) {
		interval = 250000;
	}
	accumulator += interval;

	move();
	collisionDetection();
}

void Logic::onEvent(Event& event) {
	switch (event.getType()) {
	    case GAME_STATE_CHANGED_EVENT:
			onGameStateChange((GameStateChangedEvent&) event);
			break;
		case CHANGE_PLAYER_DIRECTION_EVENT:
			DBG << "Change player direction" << std::endl;
			onChangePlayerDirection((ChangePlayerDirectionEvent&) event);
			break;
		case MOVE_MENU_POINTER_EVENT:
		    DBG("Moving Menu Pointer");
		    moveMenuPointer((MoveMenuPointerEvent&) event);
		    break;
		case MENU_SELECT_EVENT:
		    selectMenuItem();
		    break;
		case GAME_START_EVENT:
			startNewGame();
			break;
		case GAME_END_EVENT:
			gameEnd();
			break;
		default:
		    const short eventType = event.getType();
			std::stringstream ss;
			ss << "Un-Handled: " << eventType;
		    ERR(ss.str());
			break;
	}
}

void Logic::move() {
	while(accumulator >= dt) {
		integrate();
		accumulator -= dt;
	}
	interpolate(accumulator);
}

void Logic::collisionDetection() {
	EntityList toCheckAgainst = allObjects;
	//Scan for player collisions
	EntityList::iterator iter;
	for (PlayerList::iterator it = allPlayers.begin(); it != allPlayers.end(); it++) {
		toCheckAgainst.erase(std::find(toCheckAgainst.begin(), toCheckAgainst.end(), *it));
		for (iter = toCheckAgainst.begin(); iter != toCheckAgainst.end(); iter++) {
			if((*it)->detectCollision(**iter)) {	//Collision
				//Fire player collision event
			}
		}
	}
	//Scan for bullets collisions
	for (BulletsList::iterator it = allBullets.begin(); it != allBullets.end(); it++) {
		toCheckAgainst.erase(std::find(toCheckAgainst.begin(), toCheckAgainst.end(), *it));
		for (iter = toCheckAgainst.begin(); iter != toCheckAgainst.end(); iter++) {
			if ((*it)->detectCollision(**iter)) {	//Collision
				//Fire bullet collision event
			}
		}
	}
}

void Logic::integrate() {
	for (MobileEntityList::iterator it = mobileObjects.begin(); it != mobileObjects.end(); it++) {
		(*it)->integrate(dt);
	}
}

void Logic::interpolate(const double &remainder) {
	const double alpha  = remainder / dt;
	for (MobileEntityList::iterator it = mobileObjects.begin(); it != mobileObjects.end(); it++) {
		(*it)->interpolate(alpha);
		if ((*it)->getMagnitude() > 0 && (*it)->getDirection() != NONE) {
			EntityMovedEvent entityMovedEvent((*it)->getID(),(*it)->getPosition());
			eventManager->fireEvent(entityMovedEvent);
		}
	}
}

void Logic::onChangePlayerDirection(ChangePlayerDirectionEvent& event) {
	for (PlayerList::iterator it = allPlayers.begin(); it != allPlayers.end(); it++) {
		(*it)->setDirection(event.getDirection());
	}
}

void Logic::addBullets(Direction dir, float mag, sf::FloatRect geo) {
	allBullets.push_back(BulletsShPtr(new Bullets(dir, mag)));
	allBullets.back()->setGeo(geo);
	mobileObjects.push_back(allBullets.back());
	allObjects.push_back(allBullets.back());
}

void Logic::generateLevel() {
	allPlayers.push_back(PlayerShPtr(new Player()));
	allPlayers.back()->setGeo(100,100,30,30);
	mobileObjects.push_back(allPlayers.back());
	allObjects.push_back(allPlayers.back());
	EntityCreatedEvent entityCreatedEvent(
		allPlayers.back()->getID(),
		allPlayers.back()->getGeo());
	eventManager->fireEvent(entityCreatedEvent);
	DBG << "Generated level" << std::endl;
}

void Logic::onGameStateChange(GameStateChangedEvent& event) {
	const short newState = event.getState();
	std::stringstream ss;
	ss << "Changing game state to " << newState;
	DBG(ss.str());
}


void Logic::moveMenuPointer(MoveMenuPointerEvent& event){
	int rc = 0;
	switch(event.getDirection()){
		case DOWN:
			currentMenuPos = ((++currentMenuPos) % 4);
			break;

		case UP:
			currentMenuPos = --currentMenuPos;
			if(currentMenuPos < 0){
				currentMenuPos = 3;
			}

			break;

		case NONE: //go nowhere. duh!
			break;

		default:
			std::stringstream ss;
			ss << "Unable to move menu pointer in direction: " << event.getDirection();
		    ERR(ss.str());
		    rc = 1;
			break;
	}

	if(!rc){ //Above was OK
		std::stringstream ss;
		ss << "New position is: " << currentMenuPos;
		DBG(ss.str());

		MenuPointerChange menuPointerChange(currentMenuPos);
		eventManager->fireEvent(menuPointerChange);
	}
}

void Logic::selectMenuItem(){
	//we have been told to activate whatever so go for it!
	switch(currentMenuPos){
		case MENU_START:{
			INFO("Start Game selected");
			//We need to start a new game!
			GameStartEvent gameStartEvent;
			eventManager->fireEvent(gameStartEvent);
			break;
		}
		case MENU_SETTINGS:{
			//Do nothing for now
			INFO("Settings selected");
			break;
		}		
		case MENU_CREDITS:{
			//Do nothing for now
			INFO("Credits selected");
			break;
		}
		case MENU_QUIT:{
			//Let's quit!
			INFO("Quit selected");
			window->close();
			break;
		}
		default:{
			std::stringstream ss;
			ss << "Unkown Posistion: " << currentMenuPos;
			ERR(ss.str());
			break;
		}
	}
}

void Logic::startNewGame(){
	//Ok so we're going to start a new game
	//first set the loading screen
	GameStateChangedEvent gameStateChangedEvent(LOADING);
	eventManager->fireEvent(gameStateChangedEvent);
	//Now we need to initalise everything
	generateLevel();
	//Now we're done show the game!
	GameStateChangedEvent gameStateChangedEvent2(IN_GAME);
	eventManager->fireEvent(gameStateChangedEvent2);

}

void Logic::gameEnd(){
	//Ok so we're ending the game just go back to menu and tidy up
	GameStateChangedEvent gameStateChangedEvent(MENU);
	eventManager->fireEvent(gameStateChangedEvent);

	allPlayers.clear();
	mobileObjects.clear();
	allObjects.clear();
}
