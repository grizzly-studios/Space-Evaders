/* 
 * File:   Application.h
 * Author: williampoynter
 *
 * Created on September 25, 2013, 1:11 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../event/IEventManager.hpp"
#include "../logic/ILogic.hpp"
#include "../view/IView.hpp"
#include "../view/KeyboardListener.h"
#include "../view/UserInput.h"

namespace gs {

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
        bool verbose;
        bool flush;
        unsigned int FR;
        unsigned int AL;
        unsigned int WIDTH, HEIGHT;
        sf::ContextSettings settings;
        sf::RenderWindow *window;
};

}

#endif	/* APPLICATION_H */

