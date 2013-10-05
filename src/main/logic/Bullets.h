/* 
 * File:   Bullets.h
 * Author: williampoynter
 *
 * Created on October 5, 2013, 9:44 AM
 */

#ifndef BULLETS_H
#define	BULLETS_H

#include "MobileEntity.h"

namespace gs {

	class Bullets : public MobileEntity {
	public:
		Bullets();
		Bullets(const Bullets& orig);
		virtual ~Bullets();
	private:

	};

}

#endif	/* BULLETS_H */

