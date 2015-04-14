/* 
 * File:   Player.h
 * Author: williampoynter
 *
 * Created on October 5, 2013, 9:49 AM
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include "MobileEntity.h"
#include "effects/FrictionMultiplier.h"
#include "effects/Invincible.h"
#include "effects/Force.h"

namespace gs {

class Player;

typedef std::shared_ptr<Player> PlayerShPtr;
typedef std::list<PlayerShPtr> PlayerList;

class Player : public MobileEntity {
public:
	Player(double *_gameTime);
	Player(const Player& orig);
	virtual ~Player();

	virtual void tick(const long int &deltaTime);

	void hit();
	void lifeUp();
	void lifeDown();
	int livesLeft();
	void kill();

	virtual void integrate();
	virtual void advancer(MobileEntityShPtr bullets);

	void scoreUp(int value);
	void scoreDown(int value);
	int  getScore() const;

	void setInvincible(bool _invincible);
	bool isInvincible();

	void respawn();

	static PlayerShPtr create(double *_gameTime);
	static void destroy(unsigned int _ID);
	virtual void destroy();
	static std::list<PlayerShPtr> all;

	friend class Force<Player>;

private:
	double *gameTime;
	int score;
	int lives;
	IEffectList effects;
	sf::Vector2f effectForce;

	bool invincible;
};

typedef std::shared_ptr<Player> PlayerShPtr;
}

#endif	/* PLAYER_H */

