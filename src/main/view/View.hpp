#ifndef VIEW_H
#define	VIEW_H

#include <tr1/memory>
#include <map>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IView.hpp"

#include "../event/EntityCreatedEvent.h"
#include "../event/EntityMovedEvent.h"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"

namespace gs {

// TODO: Extract this typdef to a single place (also defined in Application.h at present)
typedef std::tr1::shared_ptr<sf::RenderWindow> RenderWindowShPtr;
typedef std::tr1::shared_ptr<sf::Sprite> SpriteShPtr;
typedef std::map<short, SpriteShPtr> SpriteMap;

class View : public IView, public IEventListener {
public:
	View(IEventManagerPtr _eventManager, RenderWindowShPtr _window);
	virtual ~View();
	virtual void update();
	virtual void render();
	virtual void onEvent(Event& event);
private:
	void onEntityCreated(EntityCreatedEvent& event);
	void onEntityMoved(EntityMovedEvent& event);

	IEventManagerPtr eventManager;
	RenderWindowShPtr window;
	sf::Texture texture;
	SpriteMap spriteMap;
};

}

#endif	/* VIEW_H */
