/* 
 * File:   IPausedScreen.h
 * Author: williampoynter
 *
 * Created on October 13, 2014, 18:08 PM
 */

#ifndef IPAUSEDSCREEN_H
#define	IPAUSEDSCREEN_H

#include "../../IScreen.h"

namespace gs {
	
class IPausedScreen : public IScreen {
public:
	virtual void update() = 0;
	virtual void render(RenderWindowShPtr) = 0;
	
	virtual ScreensEnum getType() const = 0;
};

typedef std::shared_ptr<IPausedScreen> IPausedScreenShPtr;
	
}

#endif	/* IPAUSEDSCREEN_H */

