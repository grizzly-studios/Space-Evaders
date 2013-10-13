#ifndef VIEW_H
#define	VIEW_H

#include "IView.hpp"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"
#include "UserInput.h"

namespace gs {

class View : public IView, public IEventListener {
public:
	View(IEventManagerPtr _eventManager, IUserInputShPtr _userInput);
	~View();
	virtual void update();
	virtual void render();
	virtual void onEvent(Event& event);
private:
	IEventManagerPtr eventManager;
	IUserInputShPtr userInput;
};

}

#endif	/* VIEW_H */
