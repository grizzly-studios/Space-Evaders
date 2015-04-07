/* 
 * File:   ICreditsScreen.h
 * Author: Will Poynter
 *
 * Created on April 5, 2015, 11:44 AM
 */

#ifndef ICREDITSSCREEN_H
#define	ICREDITSSCREEN_H

#include "../../IScreen.h"

namespace gs {
	
class ICreditsScreen : public IScreen {
public:
	virtual void update() = 0;
	virtual void render(RenderWindowShPtr) = 0;
	
	virtual ScreensEnum getType() const = 0;
};

typedef std::shared_ptr<ICreditsScreen> ICreditsScreenShPtr;
	
}

#endif	/* ICREDITSSCREEN_H */

