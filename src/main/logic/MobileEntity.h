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
#include <cmath>
#include <functional>

#include "../app/Globals.h"

namespace gs {

class MobileEntity;
	
enum Direction {NONE, UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT, ALL, DIRCOUNT};

typedef std::function<sf::Vector2f(
		double,					//h
		sf::Vector2f*,			//state
		float,					//mass
		float,					//max_speed
		sf::Vector2f,			//velocity
		sf::Vector2f,			//friction
		sf::Vector2f)			//force
>	AccelerationFunc;

sf::Vector2f DefaultAccelerator(
		double,					//h
		sf::Vector2f*,			//state
		float,					//mass
		float,					//max_speed
		sf::Vector2f,			//velocity
		sf::Vector2f,			//friction
		sf::Vector2f			//force
);

typedef std::shared_ptr<MobileEntity> MobileEntityShPtr;
typedef std::list<MobileEntityShPtr> MobileEntityList;

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

	virtual void tick(const long int &deltaTime);

	float getMaxSpeed() const;
	void setMaxSpeed(float _max_speed);
	
	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f &_velocity);
	
	float getMass() const;
	void setMass(float _mass);
	
	sf::Vector2f getForce() const;
	void setForce(const sf::Vector2f &_force);
	void safeSetForce(const sf::Vector2f &_force);
	
	sf::Vector2f getFriction() const;
	void setFriction(const sf::Vector2f &_friction);
	
	sf::Vector2f getPrevPosition();
	void setPosition(const sf::Vector2f &pos);
	void setPosition(float x, float y);
	void setGeo(const sf::FloatRect &_geo);
	void setGeo(float x, float y, float w, float h);
	bool hasMoved();
	virtual sf::Vector2f getVector(const Direction &dir, const float &mag) const;
	virtual void stop(Direction blockDir = ALL);
	
	/**
	 * Integrate function
	 * This is the key function of a mobile object. The time elapsed since
	 * the object was last moved is used to calculate the new displacement of
	 * the object.
	 * @param dt Time interval since last move call
	 */
	virtual void integrate();
	virtual void interpolate(const double &alpha);
	virtual bool detectCollision(const Entity &entity);
	virtual bool isOutOfBounds(const sf::FloatRect &bound);
	virtual bool isOutOfBounds(const sf::FloatRect &bounds, sf::Vector2f& offset);
	virtual void disableDir(Direction _dir);
	virtual void enableDir(Direction _dir);
	virtual void enableAllDir();
	virtual std::list<Direction> getDisabledDirections() const;
	virtual bool isDirDisabled(Direction _dir);

	static void seth(const double &_h) {h = _h;}
	static double geth() {return h;}
	void setAccelerationFunc(AccelerationFunc fn);

	static MobileEntityShPtr create();
	static void destroy(unsigned int _ID);
	virtual void destroy();
	static std::list<MobileEntityShPtr> all;

protected:
	float max_speed;			// unit: pixel/microseconds
	sf::Vector2f velocity;		// unit: pixel/microseconds
	float mass;					// unit: ermmmm
	sf::Vector2f friction;		// unit: ermmmm
	sf::Vector2f force;			// unit: ermmmm
	sf::Vector2f state[3];
	std::list<Direction> disabledDirections;
	sf::Vector2f prevPosition;
	
	long int accumulator;
	static long int h;
	
	AccelerationFunc acceleration;

	Direction shortToDirection(short dir);
};
	
}

#endif	/* MOBILEENTITY_H */

