#ifndef I_VIEW_HPP
#define	I_VIEW_HPP

#include <memory>

#include "IScreen.h"

namespace gs {

class IView {
public:
	virtual void init() = 0;
	virtual void update(long int elapsed) = 0;
	virtual void render() = 0;
	virtual void addScreen(IScreenShPtr) = 0;
	
};

typedef std::shared_ptr<IView> IViewPtr;

}

#endif	/* I_VIEW_HPP */
