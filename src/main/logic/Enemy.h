/* 
 * File:   Enemy.h
 * Author: williampoynter
 *
 * Created on October 5, 2013, 9:53 AM
 */

#ifndef ENEMY_H
#define	ENEMY_H

#include "Entity.h"

namespace gs {

class Enemy : public Entity {
public:
	Enemy();
	Enemy(const Enemy& orig);
	virtual ~Enemy();
private:

};

}

#endif	/* ENEMY_H */

