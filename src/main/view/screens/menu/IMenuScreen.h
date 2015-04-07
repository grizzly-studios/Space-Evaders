/* 
 * File:   IMenuScreen.h
 * Author: williampoynter
 *
 * Created on October 12, 2014, 1:40 PM
 */

#ifndef IMENUSCREEN_H
#define	IMENUSCREEN_H

#include "../../IScreen.h"
#include "MenuItemEnum.hpp"

#define MENU_CAST std::static_pointer_cast<IMenuScreen>(screens[MENU_SCREEN])

namespace gs {
	
class IMenuScreen : public IScreen {
public:
	virtual void update() = 0;
	virtual void render(RenderWindowShPtr) = 0;
	
	virtual void setMenuPos(int) = 0;
	virtual void moveMenuPos(int) = 0;
	virtual int getMenuPos() = 0;
	virtual void setSelected(MenuItem) = 0;
	virtual MenuItem getSelected() = 0;
	
	virtual ScreensEnum getType() const = 0;
};

typedef std::shared_ptr<IMenuScreen> IMenuScreenShPtr;
	
}

#endif	/* IMENUSCREEN_H */

