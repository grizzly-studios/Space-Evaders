/* 
 * File:   IStyleManager.h
 * Author: williampoynter
 *
 * Created on October 12, 2014, 12:52 PM
 */

#ifndef ISTYLEMANAGER_H
#define	ISTYLEMANAGER_H

#include <memory>

#include <SFML/Graphics/Font.hpp>

#include "../util/Logger.h"

namespace gs {

enum class StyleGroup {DEFAULT, HUD};

class IStyleManager {
public:
	virtual short getWidth() =0;
	virtual short getHeight() =0;
	
	virtual std::string getAssetPath() =0;
	virtual std::string getAssetPath(std::string) =0;

	virtual void setFont(StyleGroup, std::string) =0;
	virtual void setFont(StyleGroup, sf::Font) =0;
	virtual sf::Font& getFont(StyleGroup = StyleGroup::DEFAULT) =0;
};

typedef std::shared_ptr<IStyleManager> IStyleManagerShPtr;

}

#endif	/* ISTYLEMANAGER_H */

