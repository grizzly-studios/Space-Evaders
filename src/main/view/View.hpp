#ifndef VIEW_H
#define	VIEW_H

#include "IView.hpp"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"

namespace gs {

class View : public IView, public IEventListener {
public:
	View(IEventManagerPtr _eventManager);
	~View();
	virtual void update();
	virtual void render();
	virtual void onEvent(Event& event);
private:
	IEventManagerPtr eventManager;
};

}

#endif	/* VIEW_H */
