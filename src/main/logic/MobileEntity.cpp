/* 
 * File:   MobileEntity.cpp
 * Author: williampoynter
 * 
 * Created on October 4, 2013, 12:23 AM
 */

#include "MobileEntity.h"

using namespace gs;

long int MobileEntity::h = 0;
std::list<MobileEntityShPtr> MobileEntity::all;

MobileEntity::MobileEntity() : 
Entity(),
velocity(0,0),
force(0,0),
accumulator(0) {
	using namespace std::placeholders;
	acceleration = std::bind(DefaultAccelerator, _1, _2, _3, _4, _5, _6, _7);
}

MobileEntity::MobileEntity(const MobileEntity& orig) : Entity(orig) {
	disabledDirections = orig.getDisabledDirections();
	max_speed = orig.getMaxSpeed();
	mass = orig.getMass();
	friction = orig.getFriction();
	setGeo(orig.getGeo());
}

MobileEntity::~MobileEntity() {
}

MobileEntityShPtr MobileEntity::create() {
	all.push_back(MobileEntityShPtr(new MobileEntity()));
	Entity::all.push_back(all.back());
	return all.back();
}

void MobileEntity::destroy(unsigned int _ID) {
	all.remove_if(cleaner(_ID));
	Entity::all.remove_if(cleaner(_ID));
}

void MobileEntity::destroy() {
	destroy(getID());
}

void MobileEntity::tick(const long int &deltaTime) {
	accumulator += deltaTime;
	while(accumulator >= h) {
		integrate();
		accumulator -= h;
	}
	interpolate(accumulator / h);
}

float MobileEntity::getMaxSpeed() const {
	return max_speed;
}

void MobileEntity::setMaxSpeed(float _max_speed) {
	max_speed = _max_speed;
}

sf::Vector2f MobileEntity::getVelocity() const {
	return velocity;
}

void MobileEntity::setVelocity(const sf::Vector2f &_velocity) {
	velocity = _velocity;
	
	float dist_x = velocity.x * h;
	float dist_y = velocity.y * h;
	
	state[0].x = state[1].x - dist_x;
	state[2].x = state[1].x + dist_x;
	
	state[0].y = state[1].y - dist_y;
	state[2].y = state[1].y + dist_y;
}

float MobileEntity::getMass() const {
	return mass;
}

void MobileEntity::setMass(float _mass) {
	mass = _mass;
}

sf::Vector2f MobileEntity::getFriction() const {
	return friction;
}

void MobileEntity::setFriction(const sf::Vector2f &_friction) {
	friction = _friction;
}

sf::Vector2f MobileEntity::getForce() const {
	return force;
}

void MobileEntity::setForce(const sf::Vector2f &_force) {
	force = _force;
}

void MobileEntity::safeSetForce(const sf::Vector2f &_force) {
	sf::Vector2f newForce = _force;
	//Add code to protect against forcing through objects
	if (isDirDisabled(LEFT) && newForce.x < 0) {
		newForce.x = 0;
	}
	if (isDirDisabled(UP) && newForce.y < 0) {
		newForce.y = 0;
	}
	if (isDirDisabled(RIGHT) && newForce.x > 0) {
		newForce.x = 0;
	}
	if (isDirDisabled(DOWN) && newForce.y > 0) {
		newForce.y = 0;
	}
	force = newForce;
}

sf::Vector2f MobileEntity::getVector(const Direction &dir, const float &mag) const {
	sf::Vector2f vector;
	
	float x_mag = mag;
	float y_mag = mag;

	const float rootTwoOverTwo = 0.70710678118;

	switch(dir) {
		case UP :
			y_mag *= -1;
		case DOWN :
			x_mag = 0;
			break;
		case LEFT :
			x_mag *= -1;
		case RIGHT :
			y_mag = 0;
			break;
		case UPRIGHT :
			x_mag *= rootTwoOverTwo;
			y_mag *= -rootTwoOverTwo;
			break;
		case DOWNRIGHT :
			x_mag *= rootTwoOverTwo;
			y_mag *= rootTwoOverTwo;
			break;
		case UPLEFT :
			x_mag *= -rootTwoOverTwo;
			y_mag *= -rootTwoOverTwo;
			break;
		case DOWNLEFT :
			x_mag *= -rootTwoOverTwo;
			y_mag *= rootTwoOverTwo;
			break;
		case NONE :
			x_mag = 0;
			y_mag = 0;
			break;
		default:
			break;
	}
	
	vector.x = x_mag;
	vector.y = y_mag;
	return vector;
}

void MobileEntity::integrate() {
		
	state[0] = state[1];
	state[1] = state[2];
	
	sf::Vector2f accel = acceleration(h, state, mass, max_speed, velocity, friction, force);
	
	state[2].x = (2 * state[1].x) - state[0].x + (pow(h,2) * accel.x);
	state[2].y = (2 * state[1].y) - state[0].y + (pow(h,2) * accel.y);
	
	velocity.x = (state[2].x - state[0].x)/ (2 * h);
	velocity.y = (state[2].y - state[0].y)/ (2 * h);
}

void MobileEntity::interpolate(const double& alpha) {
	prevPosition.x = geo.left;
	prevPosition.y = geo.top;
	geo.left = state[2].x * alpha + state[1].x * (1. - alpha);
	geo.top = state[2].y * alpha + state[1].y * (1. - alpha);
}

bool MobileEntity::detectCollision(const Entity &entity) {
	return geo.intersects(entity.getGeo());
}

bool MobileEntity::isOutOfBounds(const sf::FloatRect& bounds) {
	sf::FloatRect intersect;
	if (geo.intersects(bounds,intersect)) {
		if (ceil(intersect.height) >= geo.height &&
			ceil(intersect.width)  >= geo.width) {
			return false;
		}	
	}
	return true;
}

bool MobileEntity::isOutOfBounds(const sf::FloatRect& bounds, sf::Vector2f& offset) {
	sf::FloatRect intersect;
	if (geo.intersects(bounds,intersect)) {
		if (ceil(intersect.height) >= geo.height &&
			ceil(intersect.width)  >= geo.width) {
			return false;
		} else {
			offset.x = (geo.left - intersect.left) + 
				((geo.left + geo.width) - (intersect.left + intersect.width));
			offset.y = (geo.top - intersect.top) + 
				((geo.top + geo.height) - (intersect.top + intersect.height));
		}
	}
	return true;
}

sf::Vector2f MobileEntity::getPrevPosition() {
	return prevPosition;
}

void MobileEntity::setPosition(const sf::Vector2f& pos) {
	Entity::setPosition(pos);
	state[0] = state[1] = state[2] = pos;
	setVelocity(velocity);
}

void MobileEntity::setPosition(float x, float y) {
	Entity::setPosition(x,y);
	state[0] = state[1] = state[2] = sf::Vector2f(x,y);
	setVelocity(velocity);
}

void MobileEntity::setGeo(const sf::FloatRect& _geo) {
	Entity::setGeo(_geo);
	state[0] = state[1] = state[2] = sf::Vector2f(_geo.left,_geo.top);
	setVelocity(velocity);
}

void MobileEntity::setGeo(float x, float y, float w, float h) {
	Entity::setGeo(x,y,w,h);
	state[0] = state[1] = state[2] = sf::Vector2f(x,y);
	setVelocity(velocity);
}

void MobileEntity::disableDir(Direction _dir) {
	disabledDirections.push_back(_dir);
	stop(_dir);
}

void MobileEntity::stop(Direction blockDir) {
	if ((blockDir == ALL || blockDir == UPRIGHT ||
		blockDir == RIGHT || blockDir == DOWNRIGHT) &&
		state[2].x > state[0].x	) {
		state[0].x = state[2].x = state[1].x;
		if (force.x > 0) {
		    force.x = 0;
		}
	}
	if ((blockDir == ALL || blockDir == UPLEFT ||
		blockDir == LEFT || blockDir == DOWNLEFT) &&
		state[2].x < state[0].x	) {
		state[0].x = state[2].x = state[1].x;
		if (force.x < 0) {
		    force.x = 0;
		}
	}
	if ((blockDir == ALL || blockDir == DOWNLEFT ||
		blockDir == DOWN || blockDir == DOWNRIGHT) &&
		state[2].y > state[0].y	) {
		state[0].y = state[2].y = state[1].y;
		if (force.y > 0) {
		    force.y = 0;
		}
	}
	if ((blockDir == ALL || blockDir == UPLEFT ||
		blockDir == UP || blockDir == UPRIGHT) &&
		state[2].y < state[0].y	) {
		state[0].y = state[2].y = state[1].y;
		if (force.y < 0) {
		    force.y = 0;
		}
	}
}

void MobileEntity::enableDir(Direction _dir) {
	disabledDirections.remove(_dir);
}

void MobileEntity::enableAllDir() {
	disabledDirections.clear();
}

std::list<Direction> MobileEntity::getDisabledDirections() const {
	return disabledDirections;
}

bool MobileEntity::isDirDisabled(Direction _dir) {
	for (std::list<Direction>::iterator it = disabledDirections.begin();
		it != disabledDirections.end(); it++) {
		if (*it == _dir) {
			return true;
		}
	}
	return false;
}

/* Takes an int input and converts to Direction Enum. *
 * Uses Bit comparison 							 	  *
 * Top (8), Left (4), Right (2), Bot (1).             *
 * Which means:                                       *
 * 		0 = No Direction 							  *
 * 		1 = Bot   		 							  *
 * 		2 = Right     								  *
 * 		3 = Bot-Right 	 							  *
 * 		4 = Left 		 							  *
 * 		5 = Bot-Left 	 							  *
 * 		8 = Top 		 							  *
 *     10 = Top-Right                                 *
 *     12 = Top-Left                                  *
 * Others = INVALID                                   */
Direction MobileEntity::shortToDirection(short dir){
	switch(dir){
		case 0:
			return NONE;

		case 1:
			return DOWN;

		case 2:
			return RIGHT;

		case 3:
			return DOWNRIGHT;

		case 4:
			return LEFT;

		case 5:
			return DOWNLEFT;

		case 8:
			return UP;

		case 10:
			return UPRIGHT;

		case 12:
			return UPLEFT;

		default:
			ERR << "Invalid Short value: " << dir << std::endl;
			return NONE;
	}
}

bool MobileEntity::hasMoved() {
	return state[1] != state[2];
}

void MobileEntity::setAccelerationFunc(AccelerationFunc fn) {
	acceleration = fn;
}

sf::Vector2f gs::DefaultAccelerator(
		double h,
		sf::Vector2f* state,
		float mass,
		float max_speed,
		sf::Vector2f velocity,
		sf::Vector2f friction,
		sf::Vector2f force
) {
	sf::Vector2f output;

	sf::Vector2f applied_force;
	sf::Vector2f applied_friction;
	if (fabs(velocity.x) > max_speed && fabs(force.x) > fabs(friction.x)) {
		applied_force.x = -friction.x;
	} else {
		applied_force.x = force.x;
	}
	if (fabs(velocity.y) > max_speed && fabs(force.y) > fabs(friction.y)) {
		applied_force.y = -friction.y;
	} else {
		applied_force.y = force.y;
	}
	
	if (fabs(velocity.x) < 0.000002 && applied_friction.x == 0) {
		state[0].x = state[1].x;
	}
	if (fabs(velocity.y) < 0.000002 && applied_friction.y == 0) {
		state[0].y = state[1].y;
	}

	if (fabs(velocity.x) < 0.000002) {
		applied_friction.x = 0;
	} else {
		applied_friction.x = -1 * (velocity.x/fabs(velocity.x)) * friction.x;
	}
	if (fabs(velocity.y) < 0.000002) {
		applied_friction.y = 0;
	} else {
		applied_friction.y = -1 * (velocity.y/fabs(velocity.y)) * friction.y;
	}
	
	output.x = (applied_force.x + applied_friction.x) / mass;
	output.y = (applied_force.y + applied_friction.y) / mass;
	
	return output;
}
