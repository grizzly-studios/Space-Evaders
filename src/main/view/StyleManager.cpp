/* 
 * File:   StyleManager.cpp
 * Author: williampoynter
 * 
 * Created on October 12, 2014, 12:49 PM
 */

#include "StyleManager.h"

using namespace gs;

const std::string StyleManager::assetPath = "assets/";

StyleManager::StyleManager() {
	setFont(StyleGroup::DEFAULT, "arial.ttf");
	setFont(StyleGroup::HUD, "joystix_monospace.ttf");
}

StyleManager::~StyleManager() {
}

short StyleManager::getWidth() {
	return WIDTH;
}

short StyleManager::getHeight() {
	return HEIGHT;
}

std::string StyleManager::getAssetPath() {
	return assetPath;
}

std::string StyleManager::getAssetPath(std::string file) {
	return assetPath + file;
}

void StyleManager::setFont(StyleGroup styleGroup, std::string fontFilePath) {
	if (!fonts[styleGroup].loadFromFile(assetPath + fontFilePath)) {
		ERR << "Cannot load font file: " << fontFilePath << std::endl;
	}
}

void StyleManager::setFont(StyleGroup styleGroup, sf::Font _font) {
	fonts[styleGroup] = _font;
} 

sf::Font& StyleManager::getFont(StyleGroup styleGroup) {
	return fonts[styleGroup];
}
