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

//MACRO definitions
#define INFO(_msg_) Logger::getInstance()->log(_msg_, INFO, __FILE__, __LINE__)
#define WARN(_msg_) Logger::getInstance()->log(_msg_, WARN, __FILE__, __LINE__)
#define ERR(_msg_) Logger::getInstance()->log(_msg_, ERR, __FILE__, __LINE__)
#define DEBUG(_msg_) Logger::getInstance()->log(_msg_, DEBUG, __FILE__, __LINE__)
#define changeLog Logger::getInstance()->changeLogging

enum LOGLEVEL {
	OFF = 0,
	FULL = 2
};

enum LOGTYPE {
	INFO = 0,
	WARN = 1,
	ERR = 2,
	DEBUG = 3
};
	
class Logger {
public:
		static Logger* getInstance();
		void log(const std::string& message, LOGTYPE type, const std::string& source, int line);
		void changeLogging(bool file, bool console, LOGLEVEL newLevel);

private:
        Logger();
		virtual ~Logger();
		
		static Logger* pLogger;
        bool fileOut;
		bool consoleOut;
		LOGLEVEL level;
};

#endif	/* LOGGER_H */
