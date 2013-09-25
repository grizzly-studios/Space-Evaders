/* 
 * File:   Game.h
 * Author: williampoynter
 *
 * Created on September 25, 2013, 6:47 PM
 */

#ifndef GAME_H
#define	GAME_H

#include <iostream>
#include <string>

#include "LogHandler.h"

class Game {
public:
        Game();
        virtual ~Game();
        
        void verbose(bool verbositiy);
        bool verbose();
        
        bool run();
        
        void before();
        void update();
        void after();
        
        friend std::ostream &operator<<(std::ostream &out, const Game &g);
        
private:

        bool vbs;
        LogHandler *log;
};

#endif	/* GAME_H */

