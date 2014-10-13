/* 
 * File:   StyleManager.cpp
 * Author: williampoynter
 * 
 * Created on October 12, 2014, 12:49 PM
 */

#include "StyleManager.h"

using namespace gs;

StyleManager::StyleManager() {
}

StyleManager::~StyleManager() {
}

short StyleManager::getWidth() {
	return WIDTH;
}

short StyleManager::getHeight() {
	return HEIGHT;
}

void StyleManager::setFont(std::string fontFilePath) {
	if (!font.loadFromFile(fontFilePath)) {
		ERR << "Cannot load font file: " << fontFilePath << std::endl;
	}
}

void StyleManager::setFont(sf::Font _font) {
	font = _font;
} 

sf::Font StyleManager::getFont() {
	return font;
}