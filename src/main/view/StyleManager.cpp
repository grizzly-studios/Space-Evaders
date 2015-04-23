/* 
 * File:   StyleManager.cpp
 * Author: williampoynter
 * 
 * Created on October 12, 2014, 12:49 PM
 */

#include "StyleManager.h"

#include <algorithm>

#if defined(__APPLE__) && not defined(DEBUG)
//Apple release specific code
#include "../../../installer/mac/ResourcePath.hpp"
//End Apple release specific code
#endif

#if defined(_WIN64) || defined(_WIN32)
//Windows specific code
#include <windows.h>
//End Windows specific code	  
#endif

using namespace gs;

const std::string StyleManager::assetPath = "assets/";

namespace {

std::string getExecutablePath() {
	static std::string execPath;

	if (execPath.size() > 0) {
		return execPath;
	}

	#if defined(_WIN64) || defined(_WIN32)
		HMODULE hModule = GetModuleHandleW(NULL);
		WCHAR path[MAX_PATH];
		int lengthWcharPath = GetModuleFileNameW(hModule, path, MAX_PATH);
		int lengthStringPath = WideCharToMultiByte(CP_UTF8, 0, path, lengthWcharPath, NULL, 0, NULL, NULL);
		execPath = std::string(lengthStringPath, 0);
		WideCharToMultiByte(CP_UTF8, 0, path, lengthWcharPath, &execPath[0], lengthStringPath, NULL, NULL);
		std::replace(execPath.begin(), execPath.end(), '\\', '/');
		execPath = execPath.substr(0, execPath.find_last_of("/") + 1);
	#endif

	return execPath;
}

}

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
#if defined(__APPLE__) && not defined(DEBUG)
	return resourcePath();
#else
	return getExecutablePath() + assetPath;
#endif
}

std::string StyleManager::getAssetPath(std::string file) {
	return getAssetPath() + file;
}

void StyleManager::setFont(StyleGroup styleGroup, std::string fontFilePath) {
	if (!fonts[styleGroup].loadFromFile(getAssetPath(fontFilePath))) {
		ERR << "Cannot load font file: " << fontFilePath << std::endl;
	}
}

void StyleManager::setFont(StyleGroup styleGroup, sf::Font _font) {
	fonts[styleGroup] = _font;
} 

sf::Font& StyleManager::getFont(StyleGroup styleGroup) {
	return fonts[styleGroup];
}
