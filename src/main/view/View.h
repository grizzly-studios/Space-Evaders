#ifndef VIEW_H
#define	VIEW_H

#include <memory>
#include <map>
#include <list>

#include "IView.hpp"

#include "../event/EntityCreatedEvent.hpp"
#include "../event/EntityDeletedEvent.hpp"
#include "../event/EntityMovedEvent.hpp"
#include "../event/GameStateChangedEvent.h"
#include "../event/GameStartEvent.h"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"
#include "../util/RandomNumberGenerator.h"
#include "UserInput.h"
#include "ISpriteFactory.hpp"

#include "../app/GameState.h"
#include "../app/Globals.h"

namespace gs {

// TODO: Extract this typdef to a single place (also defined in Application.h at present)
typedef std::list<sf::RectangleShape> RectShapeList;
typedef std::map<short, sf::Sprite> SpriteMap;
typedef std::list<sf::Sprite> SpriteList;

class View : public IView, public IEventListener {
public:
	View(IEventManagerPtr _eventManager, RenderWindowShPtr _window, IUserInputShPtr _userInput,
			ISpriteFactoryShPtr _sprite_factory);
	virtual ~View();

	virtual void init();
	virtual void update();
	virtual void render();
	virtual void onEvent(Event& event);
	virtual void addScreen(IScreenShPtr);
private:
	void initBackground();
	void initHud();
	void onEntityCreated(EntityCreatedEvent& event);
	void onEntityMoved(EntityMovedEvent& event);
	void onEntityDeleted(EntityDeletedEvent& event);
	void onGameStateChanged(GameStateChangedEvent& event);
	void moveMenuPointer(MenuActionEvent &event);
	void moveMenuBack();
	void selectMenuItem();

	void loadAssets();

	void inGameRender();
	void introRender();

	void gameOver();

	IEventManagerPtr eventManager;
	RenderWindowShPtr window;
	IUserInputShPtr userInput;
	ISpriteFactoryShPtr spriteFactory;

	int width;
	int height;

	RectShapeList stars;
	SpriteMap spriteMap;
	SpriteList hudSprites;
	sf::Font hudFont;
	sf::Text levelText;
	sf::Text waveText;
	sf::Text scoreText;
	sf::Text multiText;

	// Draw grid (for debugging)
	void drawGrid();

	GameState gameState;
	
	std::map<ScreensEnum, IScreenShPtr> screens;
};

}

#endif	/* VIEW_H */
