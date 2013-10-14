/* 
 * File:   Obstacle.h
 * Author: williampoynter
 *
 * Created on October 5, 2013, 9:59 AM
 */

#ifndef OBSTACLE_H
#define	OBSTACLE_H

#include "Entity.h"

namespace gs {

class Obstacle : public Entity {
public:
	Obstacle();
	Obstacle(const Obstacle& orig);
	virtual ~Obstacle();
private:

};

}

#endif	/* OBSTACLE_H */

