#include "Logic.h"

#include <algorithm>
#include <sstream>
#include <vector>
#include <SFML/System/Vector2.hpp>

#include "../util/Logger.h"
#include "../app/Globals.h"

using namespace gs;

namespace {

sf::Vector2f getTilePosition(int colIndex, int rowIndex) {
	sf::Vector2f vec;

	if (colIndex >= 0 && colIndex < GBL::COLS && rowIndex >= 0 && rowIndex < GBL::ROWS) {
		vec.x = colIndex * GBL::TILE_WIDTH + GBL::TILE_WIDTH;
		vec.y = rowIndex * GBL::TILE_WIDTH + GBL::TILE_WIDTH;
	} else {
		ERR << "Tile indices out of range" << std::endl;
	}

	return vec;
}

}

Logic::Logic(IEventManagerPtr _eventManager) : eventManager(_eventManager),
	randomNumberGenerator(time(NULL)), level(1), wave(1) {
	clock = new sf::Clock();
	gameTime = 0;
	accumulator = 0;
	MobileEntity::seth(12500);
	advanceUntil = 0;
	startAdvance = false;
	advancing = false;
}

Logic::~Logic() {
	DBG << "Destroyed" << std::endl;
	delete clock;
}

void Logic::update(long int elapsed) {
	long int interval = elapsed;
	if (interval > 250000) {
		interval = 250000;
	}

	if (gameState == IN_GAME) {
		accumulator += interval;
		gameTime += round(float(elapsed)/1000.f);

		for (MobileEntityShPtr mobileEntity : mobileObjects) {
			mobileEntity->tick(interval);
			if (mobileEntity->hasMoved()) {
				EntityMovedEvent entityMovedEvent(mobileEntity->getID(),mobileEntity->getPosition());
				eventManager->fireEvent(entityMovedEvent);
			}
		}

		collisionDetection();
		boundsCheck();
		advancePlayers();
		cleanUp();
		spawn();
		checkEnd();

	}
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

void Logic::collisionDetection() {
	EntityList toCheckAgainst = allObjects;
	//Scan for player collisions
	EntityList::iterator iter;
	for (PlayerShPtr player : allPlayers) {

		toCheckAgainst.erase(std::find(toCheckAgainst.begin(), toCheckAgainst.end(), player));
		for (iter = toCheckAgainst.begin(); iter != toCheckAgainst.end(); iter++) {
			if(player->detectCollision(**iter)) {	//Collision
				DBG << "Player ID " << player->getID() << " has been hit." << std::endl;
				player->hit();
				break;
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
			DBG << "Bullet ID " << (*it)->getID() << " is out of bounds. Adding to remove list." << std::endl;
			toBeRemoved.push_back(*it);
			if (advanceUntil < gameTime) {
				advanceUntil = gameTime;
				startAdvance = true;
			}
			advanceUntil += 30;
		}
	}
}

void Logic::advancePlayers() {
	if (startAdvance) {
		startAdvance = false;
		advancing = true;
		for (PlayerShPtr player : allPlayers) {
			sf::Vector2f current = player->getForce();
			sf::Vector2f advancer(0,0);
			if (advanceUntil > gameTime && current.y >= 0) {
				advancer = player->getVector(UP, 50.f/1000000.f);
			}
			player->safeSetForce(current + advancer);
		}
	}
	if (advanceUntil < gameTime && advancing) {
		advancing = false;
		for (PlayerShPtr player : allPlayers) {
			sf::Vector2f current = player->getForce();
			if (current.y < 0) {
				current.y = 0;
				player->safeSetForce(current);
			}
		}
	}
}

void Logic::cleanUp() {
	for (EntityList::iterator it = toBeRemoved.begin(); it != toBeRemoved.end(); it++) {
		DBG << "Erasing entity ID: " << (*it)->getID() << std::endl;
		removeEntity((*it)->getID());
	}
	toBeRemoved.clear();
}

void Logic::spawn() {
	if (gameTime > nextBulletSpawn) {
		nextBulletSpawn += bulletInterval;
		generateBullets();
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
		sf::Vector2f engines = (*it)->getVector(event.getDirection(), 50.f/1000000.f);
		sf::Vector2f advancer(0,0);
		if (advanceUntil > gameTime) {
			advancer = (*it)->getVector(UP, 50.f/1000000.f);
		}
		(*it)->safeSetForce(engines + advancer);
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
	// Create player
	allPlayers.push_back(PlayerShPtr(new Player(&gameTime)));
	const sf::Vector2f playerPos = getTilePosition(6, 17);
	allPlayers.back()->setGeo(playerPos.x, playerPos.y,
			GBL::SCREEN_SPRITE_WIDTH, GBL::SCREEN_SPRITE_WIDTH);
	mobileObjects.push_back(allPlayers.back());
	allObjects.push_back(allPlayers.back());

	EntityCreatedEvent entityCreatedEvent(
		allPlayers.back()->getID(),
		PLAYER_ENTITY,
		allPlayers.back()->getGeo());
	eventManager->fireEvent(entityCreatedEvent);

	// Create enemies
	for (int i=0; i<GBL::NUMBER_ENEMIES; i++) {
		const sf::Vector2f enemyPos = getTilePosition(i, 1);
		allObjects.push_back(EnemyShPtr(new Enemy()));
		allObjects.back()->setGeo(enemyPos.x, enemyPos.y, GBL::TILE_WIDTH, GBL::TILE_WIDTH);

		EntityCreatedEvent entityCreatedEvent2(
			allObjects.back()->getID(),
			ENEMY_ENTITY,
			allObjects.back()->getGeo());
		eventManager->fireEvent(entityCreatedEvent2);
	}

	INFO << "Generated level" << std::endl;

	generateBullets();
	bulletInterval = 3000;
	nextBulletSpawn = gameTime + bulletInterval;
}

void Logic::generateBullets() {
	const int NUM_ENEMIES_NOT_FIRING = 2;

	std::vector<int> firingEnemyIndices;
	for (int i=0; i<GBL::NUMBER_ENEMIES; i++) {
		firingEnemyIndices.push_back(i);
	}

	std::random_shuffle(firingEnemyIndices.begin(), firingEnemyIndices.end());
	for (int i=0; i<NUM_ENEMIES_NOT_FIRING; i++) {
		firingEnemyIndices.pop_back();
	}

	float minSpeedForLevel = GBL::MIN_LEVEL_START_SPEED + (GBL::LEVEL_START_SPEED_INCREMENT * (level -1));
	float waveSpeedIncrement = (GBL::MAX_BULLET_SPEED - minSpeedForLevel) / (GBL::MIN_NUMBER_WAVES - 1);
	float speedForWave = minSpeedForLevel + (waveSpeedIncrement * (wave -1));

	for (int enemyIndex : firingEnemyIndices) {
		// Position of the tile containing the bullet
		const sf::Vector2f bulletTilePos = getTilePosition(enemyIndex, 2);
		allBullets.push_back(BulletsShPtr(new Bullets(sf::Vector2f(0, 0.0001))));
		allBullets.back()->setGeo(bulletTilePos.x + 12, bulletTilePos.y + 10, GBL::TILE_WIDTH - 24, GBL::TILE_WIDTH - 20);
		mobileObjects.push_back(allBullets.back());
		allObjects.push_back(allBullets.back());

		EntityCreatedEvent entityCreatedEvent(
			allObjects.back()->getID(),
			BULLET_ENTITY,
			allObjects.back()->getGeo());
		eventManager->fireEvent(entityCreatedEvent);
	}
}

void Logic::onGameStateChange(GameStateChangedEvent& event) {
	gameState = event.getState();
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
	allBullets.clear();
	mobileObjects.clear();
	allObjects.clear();
}

void Logic::checkEnd(){

	int livesLeft = 0;
	for (PlayerShPtr player : allPlayers) {
		livesLeft += player->livesLeft();
	}

	if(livesLeft <= 0){
		GameStateChangedEvent gameStateChangedEvent(GAMEOVER);
		eventManager->fireEvent(gameStateChangedEvent);
	}
}
