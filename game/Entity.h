/* 
 * File:   Entity.h
 * Author: williampoynter
 *
 * Created on September 25, 2013, 10:20 PM
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
        Entity();
        Entity(const Entity& orig);
        Entity(const sf::Texture& orig);
        Entity(const sf::Sprite& orig);
        virtual ~Entity();
        
        sf::Texture getTexture() const;
        sf::Sprite getSprite() const;
        
        unsigned int getX();
        unsigned int getY();
        
        sf::Sprite operator()() const;
        
        bool collision(const sf::Rect<float> &rectangle);
        
private:
        sf::Texture *texture;
        sf::Sprite *sprite;
        
        unsigned int x;
        unsigned int y;
};

#endif	/* ENTITY_H */

