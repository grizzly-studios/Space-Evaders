#ifndef LOGIC_H
#define	LOGIC_H

#include <iostream>
#include <list>
#include <algorithm>
#include <iomanip>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "ILogic.hpp"
#include "../event/IEventListener.hpp"
#include "../event/IEventManager.hpp"

#include "MobileEntity.h"
#include "Player.h"
#include "Bullets.h"

namespace gs {
	
typedef std::list<EntityShPtr> EntityList;
typedef std::list<MobileEntityShPtr> MobileEntityList;
typedef std::list<PlayerShPtr> PlayerList;
typedef std::list<BulletsShPtr> BulletsList;

class Logic : public ILogic, public IEventListener  {
public:
	Logic(IEventManagerPtr _eventManager);
	~Logic();
	virtual void update();
	virtual void onEvent(IEvent& event);
private:
	IEventManagerPtr eventManager;
	
	sf::Clock *clock;
	double accumulator;
	double dt;

	EntityList allObjects;
	MobileEntityList mobileObjects;
	PlayerList allPlayers;
	BulletsList allBullets;
	
	//Subroutines
	void move();
	void collisionDetection();

	void integrate();
	void interpolate(const double &remainder);
	
	void addBullets(Direction _dir, float _mag, sf::FloatRect geo);
};

}

#endif	/* LOGIC_H */
