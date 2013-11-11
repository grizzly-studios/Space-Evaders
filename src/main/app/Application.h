/* 
 * File:   Application.h
 * Author: williampoynter
 *
 * Created on September 25, 2013, 1:11 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <memory>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../event/EventManager.h"
#include "../event/GameStateChangedEvent.h"

#include "../logic/Logic.h"

#include "../view/View.h"
#include "../view/KeyboardListener.h"
#include "../view/UserInput.h"
#include "../view/SpriteFactory.h"

namespace gs {

typedef std::shared_ptr<sf::RenderWindow> RenderWindowShPtr;

class Application {
public:
	Application(int argc, char** argv);
	virtual ~Application();

	void init();
	void run();

private:
	void load();
	
	IEventManagerPtr eventManager;
	ILogicPtr logic;
	IViewPtr view;
	bool flush;
	unsigned int FR;
	unsigned int AL;
	unsigned int WIDTH, HEIGHT;
	sf::ContextSettings settings;
	RenderWindowShPtr window;
};

}

#endif	/* APPLICATION_H */

