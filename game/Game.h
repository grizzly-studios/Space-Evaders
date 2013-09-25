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

#include <SFML/Graphics/RenderWindow.hpp>

#include "LogHandler.h"

class Game {
public:
        Game(bool _verbose = false);
        virtual ~Game();
        
        bool run(sf::RenderWindow *window);
        void before();
        void after();
        
        friend std::ostream &operator<<(std::ostream &out, const Game &g);
        
private:

        bool verbose;
        LogHandler *log;
};

#endif	/* GAME_H */

