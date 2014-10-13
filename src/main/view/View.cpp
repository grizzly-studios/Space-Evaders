#include "View.h"

#include <random>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>

#include "../util/Logger.h"

// TODO: Refactor (duplicate constants in application layer)
#define WIDTH 480
#define HEIGHT 640

#define SCREEN_SPRITE_WIDTH 32

using namespace gs;

View::View(IEventManagerPtr _eventManager,
	RenderWindowShPtr _window,
	IUserInputShPtr _userInput,
	ISpriteFactoryShPtr _sprite_factory) : eventManager(_eventManager),
	window(_window),
	userInput(_userInput),
	spriteFactory(_sprite_factory) 
{}

View::~View() {
	DBG << "Destroyed" << std::endl;
}

void View::init() {
	render(); /* Will load the LOADING screen */
	spriteFactory->init();
	initBackground();
	initHud();
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
			screens[MENU_SCREEN]->render(window);
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
			} else {
				moveMenuPointer(menuActionEvent);
			}
			break;
		}
		default: {
			const short eventType = event.getType();
			std::stringstream ss;
			ss << "Un-Handled: " << eventType;
		    ERR << ss.str() << std::endl;
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
	std::uniform_int_distribution<int> distX(0, WIDTH);
	std::uniform_int_distribution<int> distY(0, HEIGHT);
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
	hudSprites.back().setPosition(0.0f, SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(1.0f,
			(HEIGHT - SCREEN_SPRITE_WIDTH * 2) / SCREEN_SPRITE_WIDTH);

	// Bottom-left
	hudSprites.push_back(spriteFactory->createSprite(0, 2));
	hudSprites.back().setPosition(0.0f, HEIGHT - SCREEN_SPRITE_WIDTH);

	// Bottom
	hudSprites.push_back(spriteFactory->createSprite(1, 2));
	hudSprites.back().setPosition(SCREEN_SPRITE_WIDTH,
			HEIGHT - SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(
			(WIDTH - SCREEN_SPRITE_WIDTH * 2) / SCREEN_SPRITE_WIDTH, 1.0f);

	// Bottom-right
	hudSprites.push_back(spriteFactory->createSprite(2, 2));
	hudSprites.back().setPosition(WIDTH - SCREEN_SPRITE_WIDTH,
			HEIGHT - SCREEN_SPRITE_WIDTH);

	// Right
	hudSprites.push_back(spriteFactory->createSprite(2, 1));
	hudSprites.back().setPosition(WIDTH - SCREEN_SPRITE_WIDTH,
			SCREEN_SPRITE_WIDTH);
	hudSprites.back().setScale(1.0f,
			(HEIGHT - SCREEN_SPRITE_WIDTH * 2) / SCREEN_SPRITE_WIDTH);

	// Top-right
	hudSprites.push_back(spriteFactory->createSprite(2, 0));
	hudSprites.back().setPosition(WIDTH - SCREEN_SPRITE_WIDTH, 0.0f);

	// Top
	hudSprites.push_back(spriteFactory->createSprite(1, 0));
	hudSprites.back().setPosition(SCREEN_SPRITE_WIDTH, 0.0f);
	hudSprites.back().setScale(
			(WIDTH - SCREEN_SPRITE_WIDTH * 2) / SCREEN_SPRITE_WIDTH, 1.0f);
}

void View::onEntityCreated(EntityCreatedEvent& event) {
	const short entityId = event.getEntityId();
	INFO << "Entity created with id: " << entityId << std::endl;

	// Check if we already have a sprite associated with this id
	if (spriteMap.find(entityId) != spriteMap.end()) {
		WARN << "Sprite already present for this id, should it have been destroyed?" << std::endl;
	}

	sf::Sprite sprite = spriteFactory->createSprite(1, 1);
	sprite.setPosition(event.getPosition());
	// Logic dimensions map to screen pixels 1:1
	sprite.setScale(event.getDimensions() / (float) SCREEN_SPRITE_WIDTH);

	spriteMap[event.getEntityId()] = sprite;
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
			//Do nothing for now
			INFO << "Settings selected" << std::endl;
			break;
		}		
		case MENU_CREDITS:{
			//Do nothing for now
			INFO << "Credits selected" << std::endl;
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
