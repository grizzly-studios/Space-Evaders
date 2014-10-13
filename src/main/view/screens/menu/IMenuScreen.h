/* 
 * File:   IMenuScreen.h
 * Author: williampoynter
 *
 * Created on October 12, 2014, 1:40 PM
 */

#ifndef IMENUSCREEN_H
#define	IMENUSCREEN_H

#include "../../IScreen.h"

namespace gs {
	
class IMenuScreen : public IScreen {
public:
	virtual void update() = 0;
	virtual void render(RenderWindowShPtr) = 0;
	
	virtual void setMenuPos(int) = 0;
	virtual void moveMenuPos(int) = 0;
	
	virtual ScreensEnum getType() const = 0;
};

typedef std::shared_ptr<IMenuScreen> IMenuScreenShPtr;
	
}

#endif	/* IMENUSCREEN_H */

