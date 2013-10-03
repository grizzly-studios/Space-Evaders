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

class logger {
public:
		
        logger();
		virtual ~logger();

        void log(std::string message);
		void changeLogging(bool file, bool console);

private:
        bool *fileOut;
		bool *consoleOut;
};

#endif	/* LOGGER_H */