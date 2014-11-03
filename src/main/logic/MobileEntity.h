/* 
 * File:   MobileEntity.h
 * Author: williampoynter
 *
 * Created on October 4, 2013, 12:23 AM
 */

#ifndef MOBILEENTITY_H
#define	MOBILEENTITY_H

#include "Entity.h"
#include <list>
#include "../app/Globals.h"

namespace gs {
	
enum Direction {NONE, UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT, DIRCOUNT};

/**
 * Base class for all moving objects
 */
class MobileEntity : public Entity {
public:
	/**
	 * Default constructor
	 */
	MobileEntity();
	/**
	 * Copy constructor
	 * @param orig Original mobile object to deep copy
	 */
	MobileEntity(const MobileEntity& orig);
	virtual ~MobileEntity();

	float getMagnitude() const;
	void setMagnitude(float _mag);
	Direction getDirection() const;
	void setDirection(Direction _dir);
	bool safeSetDirection(Direction _dir, Direction fallback = NONE);
	void setPosition(const sf::Vector2f &pos);
	void setPosition(float x, float y);
	void setGeo(const sf::FloatRect &_geo);
	void setGeo(float x, float y, float w, float h);
	virtual Direction isOutOfBounds() = 0; /* Returns if out of bounds and the direction it is out of bounds */
	
	/**
	 * Movement function
	 * This is the key function of a mobile object. The time elapsed since
	 * the object was last moved is used to calculate the new position of
	 * the object.
	 * @param dt Time interval since last move call
	 */
	virtual void move(const double & dt);
	virtual void integrate(const double &dt);
	virtual void interpolate(const double &alpha);
	virtual bool detectCollision(const Entity &entity);
	virtual bool isOutOfBounds(const sf::FloatRect &bound);
	virtual bool isOutOfBounds(const sf::FloatRect &bounds, sf::Vector2f& offset);
	virtual void disableDir(Direction _dir);
	virtual void enableDir(Direction _dir);
	virtual void enableAllDir();
	virtual std::list<Direction> getDisabledDirections() const;
	virtual bool isDirDisabled(Direction _dir);

protected:
	float mag;
	Direction dir;
	sf::Vector2f state[2];
	std::list<Direction> disabledDirections;
	
	virtual sf::Vector2f getVector(const double & dt) const;

	Direction shortToDirection(short dir);

};

typedef std::shared_ptr<MobileEntity> MobileEntityShPtr;
	
}

#endif	/* MOBILEENTITY_H */

