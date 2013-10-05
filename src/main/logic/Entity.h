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
		sf::Vector2f position;
		Skin *skin;
		std::string name;
	};

}

#endif	/* ENTITY_H */

