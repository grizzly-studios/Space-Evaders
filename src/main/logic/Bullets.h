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
	Bullets(Direction _dir, float _mag);
	Bullets(const Bullets& orig);
	virtual ~Bullets();

private:
};

typedef std::tr1::shared_ptr<Bullets> BulletsShPtr;

}

#endif	/* BULLETS_H */

