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
		
		float getMagnitude() const;
		void setMagnitude(float _mag);
		Direction getDirection() const;
		void setDirection(Direction _dir);
		
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
		float mag;
		Direction dir;
		sf::Vector2f state[2];
	};
	
	typedef std::tr1::shared_ptr<MobileEntity> MobileEntityShPtr;
	
}

#endif	/* MOBILEENTITY_H */

