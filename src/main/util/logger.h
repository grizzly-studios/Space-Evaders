/* 
 * File:   logger.cpp
 * Author: Robert Parker
 *
 * Created on October 3, 2013, 21:09 PM
 */
 
#ifndef LOGGER_H
#define	LOGGER_H

#if defined(_WIN64) || defined(_WIN32)
//Windows specific code
#include <windows.h>
//End Windows specific code	  
#endif

#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

enum LOGLEVEL {
	OFF = 0,
	STANDARD = 1,
	DEBUG = 2
};

enum LOGTYPE {
	INFO = 0,
	WARN = 1,
	ERR = 2
};

struct splitted{
	std::string key;
	std::string value;
};
	
class logger {
public:
		static logger* getInstance();
        void log(std::string message, LOGTYPE type);
		void log(std::string message, LOGTYPE type, std::string source);
		void changeLogging(bool file, bool console, LOGLEVEL newLevel);

private:
        std::string trim(std::string line);
		splitted split(std::string line, char token);
        logger();
		virtual ~logger();
		
		static logger* pLogger;
        bool *fileOut;
		bool *consoleOut;
		LOGLEVEL *level;
};

#endif	/* LOGGER_H */