/* 
 * File:   CShapes.cpp
 * Author: williampoynter
 * 
 * Created on September 28, 2013, 12:55 PM
 */

#include "CShapes.h"

using namespace gs;

RoundedRectangle::RoundedRectangle(const sf::Vector2f &_size, float _radius) : sf::Shape() {
	radius = _radius;
	size = _size;
	maxPoints = 10;
	update();
}

RoundedRectangle::RoundedRectangle(const RoundedRectangle& orig) : sf::Shape() {
	radius = orig.getRadius();
	size = orig.getSize();
	update();
}

RoundedRectangle::~RoundedRectangle() {
}

float RoundedRectangle::getRadius() const {
	return radius;
}

sf::Vector2f RoundedRectangle::getSize() const {
	return size;
}

int RoundedRectangle::getMaxPoints() const {
	return maxPoints;
}

void RoundedRectangle::setRadius(float _radius) {
	radius = _radius;
	update();
}

void RoundedRectangle::setSize(sf::Vector2f _size) {
	size = _size;
	update();
}

void RoundedRectangle::setMaxPoints(int _maxPoints) {
	maxPoints = _maxPoints;
	update();
}

unsigned int RoundedRectangle::getPointCount() const {
	unsigned int points = 4;
	points += 4 * ((radius < maxPoints) ? round(radius) : maxPoints);
	return points;
}

sf::Vector2f RoundedRectangle::getPoint(unsigned int index) const {
	unsigned int ppc = getPointCount() / 4;
	unsigned int subpoint = index % ppc;
	unsigned int side = floor(index/ppc);
	static const float pi = 3.141592654f;

	if (subpoint < 2) {		//Straight sides
		float height(0);
		float width(0);
		float h_radius;
		float w_radius;
		if (side % 2 == 0) {
			h_radius = 0;
			w_radius = radius;
		} else {
			h_radius = radius;
			w_radius = 0;
		}
		if (side > 1) {
			h_radius *= -1;
			w_radius *= -1;
		}
		if (subpoint == 1) {
			h_radius *= -1;
			w_radius *= -1;
		}
		if ((subpoint + side) > 0 && (subpoint + side) < 3) {
			width = size.x;
		}
		if ((subpoint + side) > 1 && (subpoint + side) < 4) {
			height = size.y;
		}
		return sf::Vector2f(width+w_radius, height+h_radius);
	} else {		//Curved corners
		float angle = pi/2;
		float x(radius), y(radius);
		angle /= (radius - 1);
		angle = (angle * (subpoint - 1)) + ((pi/2) * side);
		if (side < 2) {
			x = size.x - radius;
		}
		if (side > 0 && side < 3) {
			y = size.y - radius;
		}
		return sf::Vector2f(x+std::sin(angle)*radius, y-std::cos(angle)*radius);
	}
}
