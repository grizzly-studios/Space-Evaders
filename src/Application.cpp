/* 
 * File:   Application.cpp
 * Author: williampoynter
 * 
 * Created on September 25, 2013, 1:11 AM
 */

#include <SFML/Graphics/RenderWindow.hpp>

#include "Application.h"

Application::Application(int argc, char** argv) {
        
        verbose = false;
        flush = false;
        
        FR = 50;
        
        for (int i = 1; i < argc; i++) {
                std::string arg(argv[i]);
                if (arg == "-v") {
                        verbose = true;
                }
                if (arg == "-f") {
                        flush = true;
                }
                if (arg == "-fr") {
                        FR = atoi(argv[i+1]);
                        i++;
                }
        }
}

void Application::init() {
        
        settings.antialiasingLevel = 8;
        
        window = new sf::RenderWindow(sf::VideoMode(1024,640),"Space Evaders",sf::Style::Fullscreen, settings);
}

Application::~Application() {
}

void Application::run() {
        game = new Game(verbose);
        
        game->before();
        while(game->run(window) && window->isOpen()) {
                
                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window->close();
                    }
                    if (event.type == sf::Event::KeyPressed) {
                            if (event.key.code == sf::Keyboard::Escape) {
                                    window->close();
                            }
                    }
                }
                
                std::cout << *game;
                if (flush) {
                        std::cout.flush();
                }
        }
        game->after();
        delete game;
}