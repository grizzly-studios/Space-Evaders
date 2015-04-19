#ifndef VIEW_H
#define	VIEW_H

#include <memory>

#include "IView.hpp"

//Screens
#include "screens/menu/MenuScreen.h"
#include "screens/paused/PausedScreen.h"
#include "screens/loading/LoadingScreen.h"
#include "screens/intro/IntroScreen.h"
#include "screens/gameover/GameOverScreen.h"
#include "screens/gamewon/GameWonScreen.h"
#include "screens/credits/CreditsScreen.h"
#include "screens/game/GameScreen.h"

#include "../event/GameStateChangedEvent.h"
#include "../event/GameStartEvent.h"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"
#include "../util/RandomNumberGenerator.h"
#include "UserInput.h"

#include "../app/GameState.h"
#include "../app/Globals.h"

namespace gs {

// TODO: Extract this typdef to a single place (also defined in Application.h at present)
typedef std::list<sf::RectangleShape> RectShapeList;

class View : public IView, public IEventListener {
public:
	View(IEventManagerPtr _eventManager, RenderWindowShPtr _window, IUserInputShPtr _userInput);
	virtual ~View();

	virtual void init();
	virtual void update(long int elapsed);
	virtual void render();
	virtual void onEvent(Event& event);
	virtual void addScreen(IScreenShPtr);
private:
	void initBackground();
	void onGameStateChanged(GameStateChangedEvent& event);
	void moveMenuPointer(MenuActionEvent &event);
	void moveMenuBack();
	void selectMenuItem();

	void loadAssets();

	void inGameRender();
	void introRender();

	IEventManagerPtr eventManager;
	RenderWindowShPtr window;
	IUserInputShPtr userInput;

	int width;
	int height;

	RectShapeList stars;

	// Draw grid (for debugging)
	void drawGrid();

	GameState gameState;
	
	std::map<ScreensEnum, IScreenShPtr> screens;
};

}

#endif	/* VIEW_H */
