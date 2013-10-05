/* 
 * File:   Entity.h
 * Author: williampoynter
 *
 * Created on October 3, 2013, 11:25 PM
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include <string>

#include <SFML/Graphics.hpp>

#include "../view/Skin.h"

namespace gs {

	/**
	 * Base class for logical objects within the game.
	 */
	class Entity {
	public:
		Entity();
		Entity(const Entity& orig);
		virtual ~Entity();

		void setPosition(const sf::Vector2f &pos);
		void setPosition(float x, float y);
		sf::Vector2f getPosition() const;
		virtual void setSkin(const gs::Skin &_skin);
		virtual gs::Skin getSkin() const;
		void setName(const std::string &_name);
		std::string getName() const;
		
	protected:
		/**
		 * Position of the entity on the screen.
		 * Holds the x and y coordinate that the top left corner of the object
		 * should appear in the window.
		 */
		sf::Vector2f position;
		
		/**
		 * View object to represent Entity of the screen.
		 * Details to come.
		 */
		Skin *skin;
		
		/**
		 * Name of the Entity
		 * Holds the given name of the entity for logging and writing to the 
		 * user.
		 */
		std::string name;
	};

}

#endif	/* ENTITY_H */

