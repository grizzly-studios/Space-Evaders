/* 
 * File:   IIntroScreen.h
 * Author: Rob Parker
 *
 * Created on October 13, 2014, 23:11 PM
 */

#ifndef IINTROSCREEN_H
#define	IINTROSCREEN_H

#include "../../IScreen.h"

namespace gs {
	
class IIntroScreen : public IScreen {
public:
	virtual void update() = 0;
	virtual void render(RenderWindowShPtr) = 0;
	
	virtual ScreensEnum getType() const = 0;
};

typedef std::shared_ptr<IIntroScreen> IIntroScreenShPtr;
	
}

#endif	/* IINTROSCREEN_H */

