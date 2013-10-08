/* 
 * File:   logger.cpp
 * Author: Robert Parker
 *
 * Created on October 3, 2013, 21:09 PM
 */
 
#include "logger.h"

void logger::changeLogging(bool file, bool console){
	fileOut = new bool(file);
	consoleOut = new bool(console);
}

void logger::log(std::string message){
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