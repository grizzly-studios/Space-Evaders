/* 
 * File:   IGameOverScreen.h
 * Author: Rob Parker
 *
 * Created on April 05 2015 12:50
 */

#ifndef IGAMEOVERSCREEN_H
#define	IGAMEOVERSCREEN_H

#include "../../IScreen.h"

namespace gs {
	
class IGameOverScreen : public IScreen {
public:
	virtual void update() = 0;
	virtual void render(RenderWindowShPtr) = 0;
	
	virtual ScreensEnum getType() const = 0;
};

typedef std::shared_ptr<IGameOverScreen> IGameOverScreenShPtr;
	
}

#endif	/* IGAMEOVERSCREEN_H */

