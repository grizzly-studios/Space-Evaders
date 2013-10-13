#ifndef VIEW_H
#define	VIEW_H

#include <tr1/memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IView.hpp"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"

namespace gs {

// TODO: Extract this typdef to a single place (also defined in Application.h at present)
typedef std::tr1::shared_ptr<sf::RenderWindow> RenderWindowShPtr;
class View : public IView, public IEventListener {
public:
	View(IEventManagerPtr _eventManager, RenderWindowShPtr _window);
	virtual ~View();
	virtual void update();
	virtual void render();
	virtual void onEvent(Event& event);
private:
	IEventManagerPtr eventManager;
	RenderWindowShPtr window;
};

}

#endif	/* VIEW_H */
