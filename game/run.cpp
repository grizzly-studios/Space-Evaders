#include <SFML/Graphics.hpp>

#include "Game.h"

bool Game::run(sf::RenderWindow *window) {
        
        window->clear(sf::Color(0,0,0,255));
        
        //Main game loop
        
        window->display();
        
        return true;
}
