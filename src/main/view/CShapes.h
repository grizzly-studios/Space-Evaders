/* 
 * File:   CShapes.h
 * Author: williampoynter
 *
 * Created on September 28, 2013, 12:55 PM
 */

#ifndef CSHAPES_H
#define	CSHAPES_H

#include <cmath>

#include <SFML/Graphics/RectangleShape.hpp>

namespace gs {

class RoundedRectangle : public sf::Shape {
public:
	RoundedRectangle(const sf::Vector2f &size = sf::Vector2f(0, 0), float _radius = 0);
	RoundedRectangle(const RoundedRectangle& orig);
	virtual ~RoundedRectangle();

	float getRadius() const;
	sf::Vector2f getSize() const;
	int getMaxPoints() const;
	void setRadius(float _radius);
	void setSize(sf::Vector2f _size);
	void setMaxPoints(int _maxPoints);

	//Must overload functions
	unsigned int getPointCount() const;
	sf::Vector2f getPoint(unsigned int index) const;
private:

	float radius;
	sf::Vector2f size;
	int maxPoints;
};

}

#endif	/* CSHAPES_H */

