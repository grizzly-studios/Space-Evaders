#include "Logic.h"

#include "../util/Logger.h"
#include <sstream>

using namespace gs;

Logic::Logic(IEventManagerPtr _eventManager) : eventManager(_eventManager) {
	clock = new sf::Clock();
	accumulator = 0;
	MobileEntity::seth(12500);

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
	boundsCheck();
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
		    ERR << ss.str() << std::endl;
			break;
	}
}

void Logic::move() {
	while(accumulator >= MobileEntity::geth()) {
		integrate();
		accumulator -= MobileEntity::geth();
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

void Logic::boundsCheck(){
	//Scan for player collisions here we just bump them around
	for (PlayerList::iterator it = allPlayers.begin(); it != allPlayers.end(); it++) {
		sf::Vector2f offset;
		if ((*it)->MobileEntity::isOutOfBounds(sf::FloatRect(
			GBL::SCREEN_SPRITE_WIDTH,
			GBL::SCREEN_SPRITE_WIDTH,
			GBL::WIDTH - (GBL::SCREEN_SPRITE_WIDTH * 2),
			GBL::HEIGHT - (GBL::SCREEN_SPRITE_WIDTH * 2)),offset)) {
			if (offset.x > 0) {
				(*it)->disableDir(RIGHT);
			} else if (offset.x < 0) {
				(*it)->disableDir(LEFT);
			} else if (offset.y > 0) {
				(*it)->disableDir(DOWN);
			}
		} else {
			(*it)->enableAllDir();
		}
	}

	//Scan for bullets gone off screen (to remove)
	for (BulletsList::iterator it = allBullets.begin(); it != allBullets.end(); it++) {
		Direction oOB = (*it)->isOutOfBounds();
		if(oOB == DOWN){
			DBG << "Erasing Bullet ID: " << (*it)->getID() << std::endl;
			allBullets.erase(it);
			EntityDeletedEvent entityDeletedEvent((*it)->getID());
			eventManager->fireEvent(entityDeletedEvent);
		}
	}
}

void Logic::integrate() {
	for (MobileEntityList::iterator it = mobileObjects.begin(); it != mobileObjects.end(); it++) {
		(*it)->integrate();
	}
}

void Logic::interpolate(const double &remainder) {
	const double alpha  = remainder / MobileEntity::geth();
	for (MobileEntityList::iterator it = mobileObjects.begin(); it != mobileObjects.end(); it++) {
		(*it)->interpolate(alpha);
		if ((*it)->hasMoved()) {
			EntityMovedEvent entityMovedEvent((*it)->getID(),(*it)->getPosition());
			eventManager->fireEvent(entityMovedEvent);
		}
	}
}

void Logic::onChangePlayerDirection(ChangePlayerDirectionEvent& event) {
	for (PlayerList::iterator it = allPlayers.begin(); it != allPlayers.end(); it++) {
		(*it)->safeSetForce((*it)->getVector(event.getDirection(), 50.f/1000000.f));
	}
}

void Logic::addBullets(sf::Vector2f velocity, sf::FloatRect geo) {
	allBullets.push_back(BulletsShPtr(new Bullets(velocity)));
	allBullets.back()->setGeo(geo);
	mobileObjects.push_back(allBullets.back());
	allObjects.push_back(allBullets.back());
}

void Logic::removeEntity(unsigned int entityID) {
	class cleaner {
		unsigned int ID;
	public:
		cleaner(unsigned int _ID) : ID(_ID) {}
		bool operator() (const EntityShPtr& value) {
			return value->getID() == ID;
		}
	};
	allObjects.remove_if(cleaner(entityID));
	mobileObjects.remove_if(cleaner(entityID));
	allPlayers.remove_if(cleaner(entityID));
	allBullets.remove_if(cleaner(entityID));
	EntityDeletedEvent entityDeletedEvent(entityID);
	eventManager->fireEvent(entityDeletedEvent);
}

void Logic::generateLevel() {
	allPlayers.push_back(PlayerShPtr(new Player()));
	allPlayers.back()->setGeo(100,100,GBL::SCREEN_SPRITE_WIDTH,GBL::SCREEN_SPRITE_WIDTH);
	mobileObjects.push_back(allPlayers.back());
	allObjects.push_back(allPlayers.back());
	EntityCreatedEvent entityCreatedEvent(
		allPlayers.back()->getID(),
		allPlayers.back()->getGeo());
	eventManager->fireEvent(entityCreatedEvent);
	DBG << "Generated level" << std::endl;
}

void Logic::onGameStateChange(GameStateChangedEvent& event) {
	DBG << "Changing game state to " << event.getState() << std::endl;
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
