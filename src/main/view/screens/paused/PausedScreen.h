/* 
 * File:   PausedScreen.h
 * Author: williampoynter
 *
 * Created on October 13, 2014, 06:08 PM
 */

#ifndef PAUSEDSCREEN_H
#define	PAUSEDSCREEN_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "IPausedScreen.h"

#include "../../../util/Logger.h"
#include "../../StyleManager.h"

namespace gs {

class PausedScreen : public IPausedScreen {
public:
	PausedScreen();
	PausedScreen(IStyleManagerShPtr);
	virtual ~PausedScreen();
	
	void update();
	void render(RenderWindowShPtr);
	
	virtual ScreensEnum getType() const;
	
private:
	IStyleManagerShPtr styleManager;
};

}

#endif	/* PAUSEDSCREEN_H */

