/* 
 * File:   IGameWonScreen.h
 * Author: Al Lambert
 *
 * Created on April 18 2015 11:50
 */

#ifndef IGAMEWONSCREEN_H
#define	IGAMEWONSCREEN_H

#include "../../IScreen.h"

namespace gs {
	
class IGameWonScreen : public IScreen {
public:
	virtual void update() = 0;
	virtual void render(RenderWindowShPtr) = 0;
	
	virtual ScreensEnum getType() const = 0;
};

typedef std::shared_ptr<IGameWonScreen> IGameWonScreenShPtr;
	
}

#endif	/* IGAMEWONSCREEN_H */

