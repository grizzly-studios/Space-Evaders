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

class Bullets;

typedef std::shared_ptr<Bullets> BulletsShPtr;
typedef std::list<BulletsShPtr> BulletsList;

class Bullets : public MobileEntity {
public:
	Bullets();
	Bullets(sf::Vector2f velocity);
	Bullets(const Bullets& orig);
	virtual ~Bullets();

	virtual void tick(const long int &deltaTime);

	using MobileEntity::isOutOfBounds;
	Direction isOutOfBounds();

	static BulletsShPtr create();
	static BulletsShPtr create(sf::Vector2f velocity);
	static void destroy(unsigned int _ID);
	virtual void destroy();
	static std::list<BulletsShPtr> all;

private:
};
}

#endif	/* BULLETS_H */

