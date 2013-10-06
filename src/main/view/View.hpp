#ifndef VIEW_H
#define	VIEW_H

#include "IView.hpp"
#include "../event/IEventManager.hpp"

namespace gs {

class View : public IView {
public:
	View(IEventManagerPtr _eventManager) : eventManager(_eventManager) {}
	virtual void update() {}
	virtual void render() {}
private:
	IEventManagerPtr eventManager;
};

}

#endif	/* VIEW_H */
