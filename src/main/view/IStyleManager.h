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

class IStyleManager {
public:
	virtual short getWidth() =0;
	virtual short getHeight() =0;
	
	virtual void setFont(std::string) =0;
	virtual void setFont(sf::Font) =0;
	virtual sf::Font getFont() =0;
};

typedef std::shared_ptr<IStyleManager> IStyleManagerShPtr;

}

#endif	/* ISTYLEMANAGER_H */

