/* 
 * File:   Game.cpp
 * Author: williampoynter
 * 
 * Created on September 25, 2013, 6:47 PM
 */

#include "Game.h"

Game::Game() {
        vbs = false;
        log = new LogHandler;
}

Game::~Game() {
}

void Game::verbose(bool verbositiy) {
        vbs = verbositiy;
}

bool Game::verbose() {
        return vbs;
}

std::ostream &operator<<(std::ostream &out, const Game &g) {
        std::string item;
        while(g.log->pop(item)) {
                out << item << std::endl;
        }
        return out;
}