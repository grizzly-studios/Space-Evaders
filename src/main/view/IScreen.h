/* 
 * File:   IScreen.h
 * Author: williampoynter
 *
 * Created on October 10, 2014, 5:20 PM
 */

#ifndef ISCREEN_H
#define	ISCREEN_H

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

namespace gs {

typedef std::shared_ptr<sf::RenderWindow> RenderWindowShPtr;
	
class IScreen {
public:
	virtual void update() = 0;
	virtual void render(RenderWindowShPtr) = 0;
};

typedef std::shared_ptr<IScreen> IScreenShPtr;
	
}

#endif	/* ISCREEN_H */

