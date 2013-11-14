#ifndef VIEW_H
#define	VIEW_H

#include <memory>
#include <map>
#include <list>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "IView.hpp"

#include "../event/EntityCreatedEvent.hpp"
#include "../event/EntityMovedEvent.hpp"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"
#include "UserInput.h"
#include "ISpriteFactory.hpp"

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

	IEventManagerPtr eventManager;
	RenderWindowShPtr window;
	IUserInputShPtr userInput;
	ISpriteFactoryShPtr spriteFactory;
	RectShapeList stars;
	SpriteMap spriteMap;
	SpriteList hudSprites;
	sf::Font hudFont;
	sf::Text levelText;
	sf::Text waveText;
	sf::Text scoreText;
	sf::Text multiText;
};

}

#endif	/* VIEW_H */
