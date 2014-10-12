/* 
 * File:   IGameScreen.h
 * Author: williampoynter
 *
 * Created on October 12, 2014, 22:50 PM
 */

#ifndef IGAMESCREEN_H
#define	IGAMESCREEN_H

#include "../../IScreen.h"

namespace gs {
	
class IGameScreen : public IScreen {
public:
	virtual void update() = 0;
	virtual void render(RenderWindowShPtr) = 0;
};

typedef std::shared_ptr<IGameScreen> IGameScreenShPtr;
	
}

#endif	/* IGAMESCREEN_H */

