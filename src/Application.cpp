/* 
 * File:   Application.cpp
 * Author: williampoynter
 * 
 * Created on September 25, 2013, 1:11 AM
 */

#include "Application.h"

Application::Application(int argc, char** argv) {
        
        verbose = false;
        flush = false;
        
        for (int i = 1; i < argc; i++) {
                std::string arg(argv[i]);
                if (arg == "-v")
                        verbose = true;
                if (arg == "-f")
                        flush = true;
        }
}

Application::~Application() {
}

void Application::run() {
        game = new Game(verbose);
        
        game->before();
        while(game->run()) {
                std::cout << game;
                if (flush) {
                        std::cout.flush();
                }
        }
        game->after();
        delete game;
}