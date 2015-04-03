/* 
 * File:   ILoadingScreen.h
 * Author: williampoynter
 *
 * Created on October 13, 2014, 09:25 PM
 */

#ifndef ILOADINGSCREEN_H
#define	ILOADINGSCREEN_H

#include "../../IScreen.h"

namespace gs {
	
class ILoadingScreen : public IScreen {
public:
	virtual void update() = 0;
	virtual void render(RenderWindowShPtr) = 0;
	
	virtual ScreensEnum getType() const = 0;
};

typedef std::shared_ptr<ILoadingScreen> ILoadingScreenShPtr;
	
}

#endif	/* ILOADINGSCREEN_H */

