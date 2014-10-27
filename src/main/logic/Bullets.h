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
	Bullets(sf::Vector2f velocity);
	Bullets(const Bullets& orig);
	virtual ~Bullets();

private:
};

typedef std::shared_ptr<Bullets> BulletsShPtr;

}

#endif	/* BULLETS_H */

