/* 
 * File:   Application.h
 * Author: williampoynter
 *
 * Created on September 25, 2013, 1:11 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <tr1/memory>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../util/logger.h"

#include "../event/EventManager.h"
#include "../event/GameStateChangedEvent.h"

#include "../logic/Logic.h"

#include "../view/View.h"
#include "../view/KeyboardListener.h"
#include "../view/UserInput.h"

namespace gs {

typedef std::tr1::shared_ptr<sf::RenderWindow> RenderWindowShPtr;

class Application {
public:
	Application(int argc, char** argv);
	virtual ~Application();

	void init();
	void run();

private:
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

