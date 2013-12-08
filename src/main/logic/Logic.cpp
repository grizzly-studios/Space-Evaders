#include "Logic.h"

#include <list>
#include <SFML/System/Vector2.hpp>

#include "../util/Logger.h"

#define TILE_WIDTH 32					// tile width & height
#define COLS 13							// tilemap dimensions
#define ROWS 20
#define NUMBER_LEVELS 3
#define MIN_NUMBER_WAVES 4				// player can move back, and can hence play more than this no. of waves
#define NUMBER_ENEMIES COLS-2
#define MIN_LEVEL_START_SPEED 150.0		// units/sec (pixels in this simplistic mapping)
#define MAX_BULLET_SPEED 450.0			// max speed is the same for each level
#define LEVEL_START_SPEED_INCREMENT ((MAX_BULLET_SPEED - MIN_LEVEL_START_SPEED) / (NUMBER_LEVELS - 1))


using namespace gs;

namespace {

sf::Vector2f getTilePosition(int colIndex, int rowIndex) {
	sf::Vector2f vec;

	if (colIndex >= 0 && colIndex < COLS && rowIndex >= 0 && rowIndex < ROWS) {
		vec.x = colIndex * TILE_WIDTH;
		vec.y = rowIndex * TILE_WIDTH;
	} else {
		ERR("Tile indices out of range");
	}

	return vec;
}

}

Logic::Logic(IEventManagerPtr _eventManager) : eventManager(_eventManager),
	randomNumberGenerator(time(NULL)), level(1), wave(1) {
	clock = new sf::Clock();
	accumulator = 0;
	dt = 12500;
}

Logic::~Logic() {
	DBG("Destroyed");
	delete clock;
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
	// Create player
	allPlayers.push_back(PlayerShPtr(new Player()));
	const sf::Vector2f playerPos = getTilePosition(6, 17);
	allPlayers.back()->setGeo(playerPos.x, playerPos.y, TILE_WIDTH, TILE_WIDTH);
	mobileObjects.push_back(allPlayers.back());
	allObjects.push_back(allPlayers.back());

	EntityCreatedEvent entityCreatedEvent(
		allPlayers.back()->getID(),
		PLAYER_ENTITY,
		allPlayers.back()->getGeo());
	eventManager->fireEvent(entityCreatedEvent);

	// Create enemies
	for (int i=0; i<NUMBER_ENEMIES; i++) {
		const sf::Vector2f enemyPos = getTilePosition(1 + i, 2);
		allObjects.push_back(EnemyShPtr(new Enemy()));
		allObjects.back()->setGeo(enemyPos.x, enemyPos.y, TILE_WIDTH, TILE_WIDTH);

		EntityCreatedEvent entityCreatedEvent2(
			allObjects.back()->getID(),
			ENEMY_ENTITY,
			allObjects.back()->getGeo());
		eventManager->fireEvent(entityCreatedEvent2);
	}

	INFO("Generated level");
	generateBullets();
}

void Logic::generateBullets() {
	const int NUM_ENEMIES_NOT_FIRING = 2;

	std::list<int> firingEnemyIndices;
	for (int i=0; i<NUMBER_ENEMIES; i++) {
		firingEnemyIndices.push_back(i);
	}

	for (int i=0; i<NUM_ENEMIES_NOT_FIRING; i++) {
		int indexToRemove = randomNumberGenerator.randomNumberInRange(0, firingEnemyIndices.size());
		firingEnemyIndices.remove(indexToRemove);
	}

	level = 3;	// TODO: Remove
	wave = 4;	// TODO: Remove
	float minSpeedForLevel = MIN_LEVEL_START_SPEED + (LEVEL_START_SPEED_INCREMENT * (level -1));
	std::cout << "minSpeedForLevel " << level << ": " << minSpeedForLevel << std::endl;

	float waveSpeedIncrement = (MAX_BULLET_SPEED - minSpeedForLevel) / (MIN_NUMBER_WAVES - 1);
	std::cout << "waveSpeedIncrement: " << waveSpeedIncrement << std::endl;

	float speedForWave = minSpeedForLevel + (waveSpeedIncrement * (wave -1));
	std::cout << "speedForWave " << wave << ": " << speedForWave << std::endl;

	for (std::list<int>::const_iterator it=firingEnemyIndices.begin();
		it!=firingEnemyIndices.end(); ++it) {
		std::cout << "Generating bullet: " << (*it) << std::endl;

		// Position of the tile containing the bullet
		const sf::Vector2f bulletTilePos = getTilePosition(1 + (*it), 2);
	}
}
