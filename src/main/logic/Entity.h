/* 
 * File:   Entity.h
 * Author: williampoynter
 *
 * Created on October 3, 2013, 11:25 PM
 */

#ifndef ENTITY_H
#define	ENTITY_H

#include <string>
#include <memory>
#include <list>

#include <SFML/Graphics/Rect.hpp>

#include "../util/Logger.h"

namespace gs {

class Entity;
typedef std::shared_ptr<Entity> EntityShPtr;
typedef std::list<EntityShPtr> EntityList;

/**
 * Base class for logical objects within the game.
 */
class Entity : public std::enable_shared_from_this<Entity> {
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
	virtual void setPosition(const sf::Vector2f &pos);
	/**
	 * Set Entities position
	 * @param x New x coordinate for entity
	 * @param y New y coordinate for entity
	 */
	virtual void setPosition(float x, float y);
	/**
	 * Get Entities position
	 * @return Current position
	 */
	sf::Vector2f getPosition() const;

	void setDimensions(const sf::Vector2f &dim);
	void setDimensions(float w, float h);
	sf::Vector2f getDimensions() const;
	virtual void setGeo(const sf::FloatRect &_geo);
	virtual void setGeo(float x, float y, float w, float h);
	sf::FloatRect getGeo() const;
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
	unsigned int getID() const;

	static EntityShPtr create();
	static void destroy(unsigned int _ID);
	virtual void destroy();
	static void clean();
	static std::list<EntityShPtr> all;
	static std::list<EntityShPtr> toRemove;

protected:
	/**
	 * Position and dimensions of the entity on the screen.
	 * Holds the x and y coordinate that the top left corner of the object
	 * should appear in the window. Also contains the width and height of
	 * the object.
	 */
	sf::FloatRect geo;

	/**
	 * Name of the Entity
	 * Holds the given name of the entity for logging and writing to the
	 * user.
	 */
	std::string name;
	
private:
	static unsigned int counter;
	unsigned int ID;
};

class cleaner {
	unsigned int ID;
public:
	cleaner(unsigned int _ID) {
		ID = _ID;
	}
	bool operator()(EntityShPtr entity) {
		return entity->getID() == ID;
	}
};
	
}

#endif	/* ENTITY_H */

