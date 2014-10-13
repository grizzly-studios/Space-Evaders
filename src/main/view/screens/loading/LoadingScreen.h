/* 
 * File:   LoadingScreen.h
 * Author: williampoynter
 *
 * Created on October 13, 2014, 09:26 PM
 */

#ifndef LOADINGSCREEN_H
#define	LOADINGSCREEN_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "ILoadingScreen.h"

#include "../../../util/Logger.h"
#include "../../StyleManager.h"

namespace gs {

class LoadingScreen : public ILoadingScreen {
public:
	LoadingScreen();
	LoadingScreen(IStyleManagerShPtr);
	virtual ~LoadingScreen();
	
	void update();
	void render(RenderWindowShPtr);
	
	virtual ScreensEnum getType() const;
	
private:
	IStyleManagerShPtr styleManager;
};

}

#endif	/* LOADINGSCREEN_H */

