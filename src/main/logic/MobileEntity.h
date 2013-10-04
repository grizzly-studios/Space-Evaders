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

	class MobileEntity : public Entity {
	public:
		MobileEntity();
		MobileEntity(const MobileEntity& orig);
		virtual ~MobileEntity();
	private:

	};

}

#endif	/* MOBILEENTITY_H */

