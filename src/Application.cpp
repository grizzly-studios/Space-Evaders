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
        AL = 8;
        WIDTH = 1024; HEIGHT = 640;
        
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
                if (arg == "-al") {
                        AL = atoi(argv[i+1]);
                        i++;
                }
                if (arg == "-r") {
                        std::string resolutionString(argv[i+1]);
                        std::size_t pos = resolutionString.find_first_of("x");
                        WIDTH = atoi(resolutionString.substr(0,pos).c_str());
                        HEIGHT = atoi(resolutionString.substr(pos+1).c_str());
                        i++;
                }
        }
}

void Application::init() {
        
        settings.antialiasingLevel = AL;
        
        window = new sf::RenderWindow(sf::VideoMode(WIDTH,HEIGHT),"Space Evaders",sf::Style::Fullscreen, settings);
        window->setVerticalSyncEnabled(true);
}

Application::~Application() {
}

void Application::run() {
        
        while(window->isOpen()) {
                
        }
}