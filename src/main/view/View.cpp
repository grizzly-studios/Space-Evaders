#include "View.h"

#include <iostream>
#include <string>
#include <sstream>

#include "../util/Logger.h"

#define LEVEL_TEXT "LEVEL"
#define WAVE_TEXT  "WAVE"
#define SCORE_TEXT "SCORE"
#define MULTI_TEXT "MULTI"
#define TEXT_SIZE 16 				// pixels

using namespace gs;

View::View(IEventManagerPtr _eventManager,
	RenderWindowShPtr _window,
	IUserInputShPtr _userInput,
	ISpriteFactoryShPtr _sprite_factory)
	: eventManager(_eventManager),
	  window(_window),
	  userInput(_userInput),
	  spriteFactory(_sprite_factory),
	  width(0), height(0) {

	width = window->getSize().x;
	height = window->getSize().y;
}

View::~View() {
	DBG << "Destroyed" << std::endl;
}

void View::init() {
	/* Initially we want to show the loading screen */
	gameState = LOADING; 
	render(); 
	spriteFactory->init();
	initBackground();
	initHud();

	if (!hudFont.loadFromFile("assets/joystix_monospace.ttf")) {
		ERR << "Failed to load HUD font"  << std::endl;
	}

	const int upperTextY = GBL::SCREEN_SPRITE_WIDTH + 5;
	const int lowerTextY = height - 58;
	const int rightTextX = width - GBL::SCREEN_SPRITE_WIDTH*5;

	levelText.setFont(hudFont);
	levelText.setString(LEVEL_TEXT);
	levelText.setCharacterSize(TEXT_SIZE);
	levelText.setPosition(GBL::SCREEN_SPRITE_WIDTH, upperTextY);

	waveText.setFont(hudFont);
	waveText.setString(WAVE_TEXT);
	waveText.setCharacterSize(TEXT_SIZE);
	waveText.setPosition(rightTextX, upperTextY);

	scoreText.setFont(hudFont);
	scoreText.setString(SCORE_TEXT);
	scoreText.setCharacterSize(TEXT_SIZE);
	scoreText.setPosition(GBL::SCREEN_SPRITE_WIDTH, lowerTextY);

	multiText.setFont(hudFont);
	multiText.setString(MULTI_TEXT);
	multiText.setCharacterSize(TEXT_SIZE);
	multiText.setPosition(rightTextX, lowerTextY);

}

void View::update() {
	userInput->update();
}

void View::addScreen(IScreenShPtr screenPtr) {
	if (screens.find(screenPtr->getType()) != screens.end()) {
		WARN << "Screen " << *screenPtr << 
			" already registered to the View. Overwriting previous instance." << std::endl;
	}
	screens[screenPtr->getType()] = screenPtr;
}

void View::render() {
	//First clear up then make the standards
	window->clear();
	for (RectShapeList::const_iterator it = stars.begin(); it != stars.end(); ++it) {
		window->draw(*it);
	}

	//Now work out what else to draw
	switch (gameState) {
		case IN_GAME:
			inGameRender();
			break;
		case PAUSED:
			screens[PAUSED_SCREEN]->render(window);
			break;
		case LOADING:
			screens[LOADING_SCREEN]->render(window);
			break;
		case MENU:
			switch(MENU_CAST->getSelected()) {
				case MENU_SETTINGS:
					break;
				case MENU_CREDITS:
					screens[CREDITS_SCREEN]->render(window);
					break;
				default:
					screens[MENU_SCREEN]->render(window);
					break;
			}
			break;
		case INTRO:
			screens[INTRO_SCREEN]->render(window);
			break;
	}
	//Now display
	window->display();
}

void View::inGameRender(){
	// Draw entity sprites (GAME)
	for (SpriteMap::const_iterator it = spriteMap.begin(); it != spriteMap.end(); ++it) {
		window->draw(it->second);
	}

	// Draw HUD sprites (GAME)
	for (SpriteList::const_iterator it = hudSprites.begin(); it != hudSprites.end();
			++it) {
		window->draw(*it);
	}

	window->draw(levelText);
	window->draw(waveText);
	window->draw(scoreText);
	window->draw(multiText);

	drawGrid();

	window->display();
}

void View::onEvent(Event& event) {
	const short eventType = event.getType();
	INFO << "Received event: " << event << std::endl;

	switch (eventType) {
		case GAME_STATE_CHANGED_EVENT: {
			onGameStateChanged((GameStateChangedEvent&) event);
			break;
		}
		case ENTITY_CREATED_EVENT: {
			EntityCreatedEvent& entityCreatedEvent = (EntityCreatedEvent&) event;
			onEntityCreated(entityCreatedEvent);
			break;
		}
		case ENTITY_MOVED_EVENT: {
			EntityMovedEvent& entityMovedEvent = (EntityMovedEvent&) event;
			onEntityMoved(entityMovedEvent);
			break;
		}
		case GAME_END_EVENT: {
			gameOver();
			break;
		}
		case MENU_ACTION_EVENT: {
			MenuActionEvent menuActionEvent = (MenuActionEvent&) event;
			if (menuActionEvent.getAction() == MenuActionEvent::Action::SELECT) {
				selectMenuItem();
			} else if (menuActionEvent.getAction() == MenuActionEvent::Action::BACK) {
				moveMenuBack();
			} else {
				moveMenuPointer(menuActionEvent);
			}
			break;
		}
		case ENTITY_DELETED_EVENT: {
			EntityDeletedEvent& entityDeletedEvent = (EntityDeletedEvent&) event;
			onEntityDeleted(entityDeletedEvent);
			break;
		}
		default: {
		    ERR << "Un-Handled: " << event << std::endl;
			break;
		}
	}
}

void View::initBackground() {
	// 'Randomly' position some stars
	const int NUM_STARS = 80;
	const int STAR_WIDTH = 3;
	const int SEED = 48;

	std::mt19937 randomNumGen(SEED);
	std::uniform_int_distribution<int> distX(0, GBL::WIDTH);
	std::uniform_int_distribution<int> distY(0, GBL::HEIGHT);
	std::function<int()> genX(std::bind(distX, randomNumGen));
	std::function<int()> genY(std::bind(distY, randomNumGen));
	
	genX();
	
	for (int i=0; i<NUM_STARS; i++) {
		stars.push_back(sf::RectangleShape(sf::Vector2f(STAR_WIDTH, STAR_WIDTH)));
		stars.back().setPosition(genX(), genY());
	}
}

void View::initHud() {
	// Top-left
	hudSprites.push_back(spriteFactory->createSprite(0, 0));

	// Left
	hudSprites.push_back(spriteFactory->createSprite(0, 1));
	hudSprites.back().setPosition(0.0f, GBL::SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(1.0f,
			(GBL::HEIGHT - GBL::SCREEN_SPRITE_WIDTH * 2) / GBL::SCREEN_SPRITE_WIDTH);

	// Bottom-left
	hudSprites.push_back(spriteFactory->createSprite(0, 2));
	hudSprites.back().setPosition(0.0f, GBL::HEIGHT - GBL::SCREEN_SPRITE_WIDTH);

	// Bottom
	hudSprites.push_back(spriteFactory->createSprite(1, 2));
	hudSprites.back().setPosition(GBL::SCREEN_SPRITE_WIDTH,
			GBL::HEIGHT - GBL::SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(
			(GBL::WIDTH - GBL::SCREEN_SPRITE_WIDTH * 2) / GBL::SCREEN_SPRITE_WIDTH, 1.0f);

	// Bottom-right
	hudSprites.push_back(spriteFactory->createSprite(2, 2));
	hudSprites.back().setPosition(GBL::WIDTH - GBL::SCREEN_SPRITE_WIDTH,
			GBL::HEIGHT - GBL::SCREEN_SPRITE_WIDTH);

	// Right
	hudSprites.push_back(spriteFactory->createSprite(2, 1));
	hudSprites.back().setPosition(GBL::WIDTH - GBL::SCREEN_SPRITE_WIDTH,
			GBL::SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(1.0f,
			(GBL::HEIGHT - GBL::SCREEN_SPRITE_WIDTH * 2) / GBL::SCREEN_SPRITE_WIDTH);

	// Top-right
	hudSprites.push_back(spriteFactory->createSprite(2, 0));
	hudSprites.back().setPosition(GBL::WIDTH - GBL::SCREEN_SPRITE_WIDTH, 0.0f);

	// Top
	hudSprites.push_back(spriteFactory->createSprite(1, 0));
	hudSprites.back().setPosition(GBL::SCREEN_SPRITE_WIDTH, 0.0f);
	hudSprites.back().setScale(
			(GBL::WIDTH - GBL::SCREEN_SPRITE_WIDTH * 2) / GBL::SCREEN_SPRITE_WIDTH, 1.0f);
}

void View::onEntityCreated(EntityCreatedEvent& event) {
	const short entityId = event.getEntityId();
	INFO << "Entity created with id: " << entityId << std::endl;

	// Check if we already have a sprite associated with this id
	if (spriteMap.find(entityId) != spriteMap.end()) {
		WARN << "Sprite already present for this id, should it have been destroyed?" << std::endl;
	}

	int spriteCol = -1;
	int spriteRow = -1;
	switch (event.getEntityType()) {
		case PLAYER_ENTITY:
			spriteCol = 3;
			spriteRow = 0;
			break;
		case ENEMY_ENTITY:
			spriteCol = 3;
			spriteRow = 1;
			break;
		case BULLET_ENTITY:
			spriteCol = 3;
			spriteRow = 2;
			break;
	}

	sf::Sprite sprite = spriteFactory->createSprite(spriteCol, spriteRow,
			(sf::Vector2i)event.getDimensions());
	sprite.setPosition(event.getPosition());
	// Logic dimensions map to screen pixels 1:1
	//sprite.setScale(event.getDimensions() / (float) GBL::SCREEN_SPRITE_WIDTH);

	spriteMap[event.getEntityId()] = sprite;
}

void View::onEntityDeleted(EntityDeletedEvent& event) {
	const short entityId = event.getEntityId();
	

	// Check if we already have a sprite associated with this id
	if (spriteMap.find(entityId) == spriteMap.end()) {
		WARN << "Sprite  with ID "<< entityId << " has already been destroyed" << std::endl;
		return;
	}

	INFO << "Entity deleted with id: " << entityId << std::endl;

	spriteMap.erase(event.getEntityId());
}

void View::onEntityMoved(EntityMovedEvent& event) {
	const short entityId = event.getEntityId();
	INFO << "Entity moved with id: " << entityId << std::endl;

	// Check we have a sprite associated with this id
	SpriteMap::iterator it = spriteMap.find(entityId);
	if (it != spriteMap.end()) {
		it->second.setPosition(event.getPosition());
	} else {
		WARN << "No sprite for this id" << std::endl;
	}
}

void View::drawGrid() {
	int horizLines = (height / GBL::SCREEN_SPRITE_WIDTH) -1;
	int vertLines = (width / GBL::SCREEN_SPRITE_WIDTH) -1;
	int numVertices = horizLines * vertLines;

	sf::Vertex* vertices = new sf::Vertex[numVertices];

	int count = 0;

	for (int i=0; i<horizLines; i++) {
		vertices[count++] = sf::Vertex(sf::Vector2f(0, GBL::SCREEN_SPRITE_WIDTH + i*GBL::SCREEN_SPRITE_WIDTH));
		vertices[count++] = sf::Vertex(sf::Vector2f(width, GBL::SCREEN_SPRITE_WIDTH + i*GBL::SCREEN_SPRITE_WIDTH));
	}

	for (int i=0; i<vertLines; i++) {
		vertices[count++] = sf::Vertex(sf::Vector2f(GBL::SCREEN_SPRITE_WIDTH + i*GBL::SCREEN_SPRITE_WIDTH, 0));
		vertices[count++] = sf::Vertex(sf::Vector2f(GBL::SCREEN_SPRITE_WIDTH + i*GBL::SCREEN_SPRITE_WIDTH, height));
	}

	window->draw(vertices, numVertices, sf::Lines);

	delete[] vertices;
}

void View::onGameStateChanged(GameStateChangedEvent& event) {
	gameState = event.getState();
}

void View::moveMenuPointer(MenuActionEvent& event){
	switch(event.getAction()){
		case MenuActionEvent::Action::DOWN:
			MENU_CAST->moveMenuPos(-1);
			break;

		case MenuActionEvent::Action::UP:
			MENU_CAST->moveMenuPos(1);
			break;

		case MenuActionEvent::Action::SELECT: //go nowhere. duh!
			break;

		default:
			ERR << "Unable to move menu pointer in direction: " << event.getAction() << std::endl;
			break;
	}
}

void View::moveMenuBack() {
	if (MENU_CAST->getSelected() != MAIN_MENU) {
		MENU_CAST->setSelected(MAIN_MENU);
	}
}

void View::selectMenuItem(){
	//we have been told to activate whatever so go for it!
	switch(MENU_CAST->getMenuPos()){
		case MENU_START:{
			INFO << "Start Game selected" << std::endl;
			//We need to start a new game!
			GameStartEvent gameStartEvent;
			eventManager->fireEvent(gameStartEvent);
			break;
		}
		case MENU_SETTINGS:{
			INFO << "Settings selected" << std::endl;
			MENU_CAST->setSelected(MENU_SETTINGS);
			break;
		}		
		case MENU_CREDITS:{
			//Do nothing for now
			INFO << "Credits selected" << std::endl;
			MENU_CAST->setSelected(MENU_CREDITS);
			break;
		}
		case MENU_QUIT:{
			//Let's quit!
			INFO << "Quit selected" << std::endl;
			window->close();
			break;
		}
		default:{
			ERR << "Unknown menu selection" << MENU_CAST->getMenuPos() << std::endl;
			break;
		}
	}
}

void View::gameOver(){
	spriteMap.clear();
}
