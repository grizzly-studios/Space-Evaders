#ifndef VIEW_H
#define	VIEW_H

#include <memory>
#include <map>
#include <list>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "IView.hpp"

#include "../event/EntityCreatedEvent.hpp"
#include "../event/EntityMovedEvent.hpp"
#include "../event/MenuPointerChange.h"
#include "../event/GameStateChangedEvent.h"
#include "../event/GameStartEvent.h"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"
#include "UserInput.h"
#include "ISpriteFactory.hpp"
#include "../logic/MenuItemEnum.hpp"

#include "../app/GameState.h"

namespace gs {

// TODO: Extract this typdef to a single place (also defined in Application.h at present)
typedef std::shared_ptr<sf::RenderWindow> RenderWindowShPtr;
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
private:
	void initBackground();
	void initHud();
	void onEntityCreated(EntityCreatedEvent& event);
	void onEntityMoved(EntityMovedEvent& event);
	void onGameStateChanged(GameStateChangedEvent& event);
	void moveMenuPointer(MenuActionEvent &event);
	void selectMenuItem();

	void inGameRender();
	void pausedRender();
	void loadingRender();
	void menuRender();

	void gameOver();

	IEventManagerPtr eventManager;
	RenderWindowShPtr window;
	IUserInputShPtr userInput;
	ISpriteFactoryShPtr spriteFactory;
	sf::Texture texture;
	RectShapeList stars;
	SpriteMap spriteMap;
	SpriteList hudSprites;
	sf::Font font;
	GameState gameState;

	int menuPos;
	int currentMenuPos;
};

}

#endif	/* VIEW_H */
