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

class Enemy;

typedef std::shared_ptr<Enemy> EnemyShPtr;
typedef std::list<EnemyShPtr> EnemyList;

class Enemy : public Entity {
public:
	Enemy();
	Enemy(const Enemy& orig);
	virtual ~Enemy();

	static EnemyShPtr create();
	static void destroy(unsigned int _ID);
	virtual void destroy();
	static std::list<EnemyShPtr> all;
private:

};

}

#endif	/* ENEMY_H */

