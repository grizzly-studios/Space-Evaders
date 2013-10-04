/* 
 * File:   Entity.h
 * Author: williampoynter
 *
 * Created on October 3, 2013, 11:25 PM
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include <SFML/Graphics.hpp>

namespace gs {

	class Entity {
	public:
		Entity();
		Entity(const Entity& orig);
		virtual ~Entity();

		void setPosition(const sf::Vector2f &pos);
		void setPosition(float x, float y);
		sf::Vector2f getPosition() const;
	protected:
		sf::Vector2f position;
		
	};

}

#endif	/* ENTITY_H */

