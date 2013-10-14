/* 
 * File:   logger.cpp
 * Author: Robert Parker
 *
 * Created on October 3, 2013, 21:09 PM
 */
 
#ifndef LOGGER_H
#define	LOGGER_H

#include <string>
#include <iostream>

enum LOGLEVEL {
	OFF = 0,
	STANDARD = 1,
	DEBUG = 2
};

enum LOGTYPE {
	INFO = 0,
	WARN = 1,
	ERROR = 2
};
	
class logger {
public:
		static logger* getInstance();
        void log(std::string message, LOGTYPE type);
		void changeLogging(bool file, bool console, LOGLEVEL newLevel);

private:
        logger();
		virtual ~logger();
		
		static logger* pLogger;
        bool *fileOut;
		bool *consoleOut;
		LOGLEVEL *level;
};

#endif	/* LOGGER_H */