/* 
 * File:   StyleManager.h
 * Author: williampoynter
 *
 * Created on October 12, 2014, 12:49 PM
 */

#ifndef STYLEMANAGER_H
#define	STYLEMANAGER_H

#include "IStyleManager.h"

#include <string>

namespace gs {

class StyleManager : public IStyleManager {
public:
	StyleManager();
	virtual ~StyleManager();
	
	short getWidth();
	short getHeight();
	
	void setFont(std::string);
	void setFont(sf::Font);
	sf::Font getFont();
private:
	static const short WIDTH = 480;
	static const short HEIGHT = 640;
	
	sf::Font font;
};

}

#endif	/* STYLEMANAGER_H */

