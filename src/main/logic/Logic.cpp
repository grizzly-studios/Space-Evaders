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

		for (MobileEntityShPtr mobileEntity : MobileEntity::all) {
			mobileEntity->tick(interval);
			if (mobileEntity->hasMoved()) {
				EntityMovedEvent entityMovedEvent(mobileEntity->getID(),mobileEntity->getPosition());
				eventManager->fireEvent(entityMovedEvent);
			}
		}

		int totalScore = 0;
		bool updateScreenScore = false;
		for (PlayerShPtr player : Player::all) {
			for (BulletsShPtr bullets : Bullets::all) {
				bool passedBullet = player->advancer(bullets);
				updateScreenScore = updateScreenScore || passedBullet;
			}
			if (player->hasBeenHit()) {
				if(player->livesLeft() <= 0){
					Entity::toRemove.push_back(player);
				}
				//fireEvent of player hit to view
			}
			totalScore += player->getScore();
		}
		if (updateScreenScore) {
			ScoreChangedEvent scoreChangedEvent(totalScore);
			eventManager->fireEvent(scoreChangedEvent);
		}

		nextBulletSpawn -= interval;

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

void Logic::cleanUp() {
	for (EntityShPtr entity : Entity::toRemove) {
		EntityDeletedEvent entityDeletedEvent(entity->getID());
		eventManager->fireEvent(entityDeletedEvent);
	}
	Entity::clean();
}

void Logic::spawn() {
	if (nextBulletSpawn < 0) {
		nextBulletSpawn = bulletInterval;
		generateBullets();
	}
}

void Logic::onChangePlayerDirection(ChangePlayerDirectionEvent& event) {
	for (PlayerShPtr player : Player::all) {
		sf::Vector2f engines = player->getVector(event.getDirection(), 50.f/1000000.f);
		player->safeSetForce(engines);
	}
}

void Logic::addBullets(sf::Vector2f velocity, sf::FloatRect geo) {
	Bullets::create(velocity)->setGeo(geo);
}

void Logic::generateLevel() {
	// Create player
	PlayerShPtr player = Player::create();
	const sf::Vector2f playerPos = getTilePosition(6, 17);
	player->setGeo(playerPos.x, playerPos.y,
			GBL::SCREEN_SPRITE_WIDTH, GBL::SCREEN_SPRITE_WIDTH);

	EntityCreatedEvent entityCreatedEvent(
		player->getID(),
		PLAYER_ENTITY,
		player->getGeo());
	eventManager->fireEvent(entityCreatedEvent);

	// Create enemies
	for (int i=0; i<GBL::NUMBER_ENEMIES; i++) {
		const sf::Vector2f enemyPos = getTilePosition(i, 1);
		EnemyShPtr enemy = Enemy::create();
		enemy->setGeo(enemyPos.x, enemyPos.y, GBL::TILE_WIDTH, GBL::TILE_WIDTH);
		EntityCreatedEvent entityCreatedEvent2(
			enemy->getID(),
			ENEMY_ENTITY,
			enemy->getGeo());
		eventManager->fireEvent(entityCreatedEvent2);
	}

	INFO << "Generated level" << std::endl;

	generateBullets();
	bulletInterval = 3000000;
	nextBulletSpawn =  bulletInterval;
	endCount = 0;
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
		BulletsShPtr bullets = Bullets::create(sf::Vector2f(0, 0.0001));
		bullets->setGeo(bulletTilePos.x + 12, bulletTilePos.y + 10, GBL::TILE_WIDTH - 24, GBL::TILE_WIDTH - 20);
		EntityCreatedEvent entityCreatedEvent(
			bullets->getID(),
			BULLET_ENTITY,
			bullets->getGeo());
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

	ScoreChangedEvent scoreChangedEvent(0);
	eventManager->fireEvent(scoreChangedEvent);
}

void Logic::gameEnd(){
	//Ok so we're ending the game just go back to menu and tidy up
	GameStateChangedEvent gameStateChangedEvent(MENU);
	eventManager->fireEvent(gameStateChangedEvent);

	Player::all.clear();
	Bullets::all.clear();
	MobileEntity::all.clear();
	Entity::all.clear();
}

void Logic::checkEnd(){

	int livesLeft = 0;
	for (PlayerShPtr player : Player::all) {
		livesLeft += player->livesLeft();
		if (player->getPosition().y < GBL::WIN_HEIGHT) {
			DBG << "Player has won!" << std::endl;
			GameStateChangedEvent gameStateChangedEvent(GAMEWON);
			eventManager->fireEvent(gameStateChangedEvent);
			break;
		}
	}

	if(livesLeft <= 0){
		DBG << "All players are dead" << std::endl;
		GameStateChangedEvent gameStateChangedEvent(GAMEOVER);
		eventManager->fireEvent(gameStateChangedEvent);
	}
}
