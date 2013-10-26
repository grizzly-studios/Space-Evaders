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
#define INFO(_msg_) Logger::getInstance()->log(_msg_, INFO_TYPE, __FILE__, __LINE__)
#define WARN(_msg_) Logger::getInstance()->log(_msg_, WARN_TYPE, __FILE__, __LINE__)
#define ERR(_msg_) Logger::getInstance()->log(_msg_, ERR_TYPE, __FILE__, __LINE__)
#define DBG(_msg_) Logger::getInstance()->log(_msg_, DEBUG_TYPE, __FILE__, __LINE__)
#define CHANGE_LOG Logger::getInstance()->changeLogging

namespace gs {

enum LOGLEVEL {
	OFF = 0,
	FULL = 2
};

enum LOGTYPE {
	INFO_TYPE = 0,
	WARN_TYPE = 1,
	ERR_TYPE = 2,
	DEBUG_TYPE = 3
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

}

#endif	/* LOGGER_H */
