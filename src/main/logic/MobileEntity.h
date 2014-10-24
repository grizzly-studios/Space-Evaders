/* 
 * File:   MobileEntity.h
 * Author: williampoynter
 *
 * Created on October 4, 2013, 12:23 AM
 */

#ifndef MOBILEENTITY_H
#define	MOBILEENTITY_H

#include "Entity.h"

namespace gs {
	
enum Direction {NONE, UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT};

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

	float getMaxSpeed() const;
	void setMaxSpeed(float _max_speed);
	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f &_velocity);
	float getMass() const;
	void setMass(float _mass);
	sf::Vector2f getForce() const;
	void setForce(const sf::Vector2f &_force);
	sf::Vector2f getFriction() const;
	void setFriction(const sf::Vector2f &_friction);
	void setPosition(const sf::Vector2f &pos);
	void setPosition(float x, float y);
	void setGeo(const sf::FloatRect &_geo);
	void setGeo(float x, float y, float w, float h);
	bool hasMoved();
	virtual sf::Vector2f getVector(const Direction &dir, const float &mag) const;
	
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
protected:
	float max_speed;			// unit: pixel/microseconds
	sf::Vector2f velocity;		// unit: pixel/microseconds
	float mass;					// unit: ermmmm
	sf::Vector2f friction;	// unit: ermmmm
	sf::Vector2f force;			// unit: ermmmm
	sf::Vector2f state[3];
};

typedef std::shared_ptr<MobileEntity> MobileEntityShPtr;
	
}

#endif	/* MOBILEENTITY_H */

