#include "Logic.h"

#include "../util/Logger.h"

#define TILE_WIDTH 32		// tile width & height
#define COLS 13				// tilemap dimensions
#define ROWS 20

using namespace gs;

Logic::Logic(IEventManagerPtr _eventManager) : eventManager(_eventManager) {
	clock = new sf::Clock();
	accumulator = 0;
	dt = 12500;
}

Logic::~Logic() {
	DBG("Destroyed");
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
		case CHANGE_PLAYER_DIRECTION_EVENT:
			DBG("Change player direction");
			onChangePlayerDirection((ChangePlayerDirectionEvent&) event);
			break;
		default:
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

	float playerX = ((COLS / 2.0f) * TILE_WIDTH) - (TILE_WIDTH / 2);
	float playerY = TILE_WIDTH * 18;

	allPlayers.back()->setGeo(playerX, playerY, TILE_WIDTH, TILE_WIDTH);
	mobileObjects.push_back(allPlayers.back());
	allObjects.push_back(allPlayers.back());
	EntityCreatedEvent entityCreatedEvent(
		allPlayers.back()->getID(),
		allPlayers.back()->getGeo());
	eventManager->fireEvent(entityCreatedEvent);
	DBG("Generated level");
}
