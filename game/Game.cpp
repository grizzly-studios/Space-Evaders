/* 
 * File:   Game.cpp
 * Author: williampoynter
 * 
 * Created on September 25, 2013, 6:47 PM
 */

#include "Game.h"

Game::Game(bool _verbose) {
        verbose = _verbose;
        log = new LogHandler;
}

Game::~Game() {
}

std::ostream &operator<<(std::ostream &out, const Game &g) {
        std::string item;
        while(g.log->pop(item)) {
                out << item << std::endl;
        }
        return out;
}