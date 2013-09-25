/* 
 * File:   Application.h
 * Author: williampoynter
 *
 * Created on September 25, 2013, 1:11 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <iostream>
#include <string>

#include "../game/Game.h"
#include "LogHandler.h"

class Application {
public:
        Application(int argc, char** argv);
        virtual ~Application();
        
        void run();

private:
        bool verbose;
        bool flush;
        Game *game;
};

#endif	/* APPLICATION_H */

