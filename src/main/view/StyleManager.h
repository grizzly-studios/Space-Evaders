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
#include <map>

namespace gs {

class StyleManager : public IStyleManager {
public:
	StyleManager();
	virtual ~StyleManager();
	
	short getWidth();
	short getHeight();
	
	std::string getAssetPath();
	std::string getAssetPath(std::string file);

	void setFont(StyleGroup styleGroup, std::string);
	void setFont(StyleGroup styleGroup, sf::Font);
	sf::Font& getFont(StyleGroup styleGroup = StyleGroup::DEFAULT);
private:
	static const short WIDTH = 480;
	static const short HEIGHT = 640;
	
	static const std::string assetPath;

	std::map<StyleGroup, sf::Font> fonts;
};

}

#endif	/* STYLEMANAGER_H */

