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
		/**
		 * Default constructor
         */
		Entity();
		/**
		 * Copy constructor
         * @param orig Original Entity to be deep copied
         */
		Entity(const Entity& orig);
		virtual ~Entity();
		
		/**
		 * Set Entities position
         * @param pos New position for entity
         */
		void setPosition(const sf::Vector2f &pos);
		/**
		 * Set Entities position
         * @param x New x coordinate for entity
         * @param y New y coordinate for entity
         */
		void setPosition(float x, float y);
		/**
		 * Get Entities position
         * @return Current position
         */
		sf::Vector2f getPosition() const;
		
		void setDimensions(const sf::Vector2f &dim);
		void setDimensions(float w, float h);
		sf::Vector2f getDimensions() const;
		
		/**
		 * Set Entities new view object
         * @param _skin New skin for entity
         */
		virtual void setSkin(const Skin &_skin);
		/**
		 * Get Entities current view object
         * @return Current view object
         */
		virtual Skin getSkin() const;
		/**
		 * Set Entities name
         * @param _name New name for entity
         */
		void setName(const std::string &_name);
		/**
		 * Get Entities current name
         * @return Current name
         */
		std::string getName() const;
		
	protected:
		/**
		 * Position of the entity on the screen.
		 * Holds the x and y coordinate that the top left corner of the object
		 * should appear in the window.
		 */
		sf::Vector2f position;
		
		sf::Vector2f dimensions;
		
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
		
		static int counter;
		int ID;
	};
	
}

#endif	/* ENTITY_H */

