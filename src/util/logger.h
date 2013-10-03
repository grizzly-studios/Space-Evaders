/* 
 * File:   logger.cpp
 * Author: Robert Parker
 *
 * Created on October 3, 2013, 21:09 PM
 */
 
#ifndef LOGGER_H
#define	LOGGER_H

#include <string>

class logger {
public:
        logger(int argc, char** argv);
		
		void init();
        void log();

private:
        bool fileOut;
		bool consoleOut;
};

#endif	/* LOGGER_H */