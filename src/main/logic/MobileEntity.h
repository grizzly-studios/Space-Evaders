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
		
		/**
		 * Movement function
		 * This is the key function of a mobile object. The time elapsed since
		 * the object was last moved is used to calculate the new position of
		 * the object.
         * @param dt Time interval since last move call
         */
		virtual void move(const double & dt)=0;
	private:

	};
	
	enum Direction {UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT};

}

#endif	/* MOBILEENTITY_H */

