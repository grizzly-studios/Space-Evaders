/* 
 * File:   logger.cpp
 * Author: Robert Parker
 *
 * Created on October 3, 2013, 21:09 PM
 */
 
#include "logger.h"

logger* logger::pLogger = NULL;

void logger::changeLogging(bool file, bool console, LOGLEVEL newLevel){
    if(pLogger == NULL){
		//We need to initalise before we change the settings
		pLogger = new logger();
	}
	fileOut = new bool(file);
	consoleOut = new bool(console);
	level = new LOGLEVEL(newLevel);
}

void logger::log(std::string message, LOGTYPE type){
	if(pLogger == NULL){
		//We need to initalise before we log out first time
		pLogger = new logger();
	}
	
	if(*consoleOut){
		std::cout << message << std::endl;
	}
	if(*fileOut){
		//Nothing for now
	}
}

logger::~logger() {
}

logger::logger(){
	fileOut = new bool(false);
	consoleOut = new bool(false);
}

logger* logger::getInstance(){
	if(pLogger == NULL){
		pLogger = new logger();
	}
	return pLogger;
}

