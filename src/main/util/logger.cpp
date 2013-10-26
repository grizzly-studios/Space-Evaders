/* 
 * File:   logger.cpp
 * Author: Robert Parker
 *
 * Created on October 3, 2013, 21:09 PM
 */
 
#include "logger.h"

Logger* Logger::pLogger = NULL;

using namespace std;

void Logger::changeLogging(bool file, bool console, LOGLEVEL newLevel){
    if(pLogger == NULL){
		//We need to initalise before we change the settings
		pLogger = new Logger();
	}
	fileOut = new bool(file);
	consoleOut = new bool(console);
	level = new LOGLEVEL(newLevel);
}

void Logger::log(string message, LOGTYPE type, string source, int line){
	if(pLogger == NULL){
		//We need to initalise before we log out first time
		pLogger = new Logger();
	}
	
	// Do first checks to determine if we should log
	if(type != ERR && *level != FULL){
		//we do not log out INFO, WARN or DEBUG on anything BUT full
		return;
	} 
	
	//Now create the logging message
	string line1;

	//Get current date and time
	time_t rawTime;
	struct tm * timeinfo;
	char timestamp [20];
	time(&rawTime);
	timeinfo = localtime (&rawTime);
	strftime (timestamp,30,"%d/%m/%Y %H:%M:%S",timeinfo);
	
	//Sort out string representation of type
	if(type == INFO){
		line1 = " - INFO";
	} else if(type == WARN){
		line1 = " - WARN";
	} else if(type == ERR){
		line1 = " - ERR!";
	} else {
		line1 = " - DEBUG";
	}
	
	//Finally append the source (if supplied)
	if(source.length() > 0){
		char numstr[21];
		sprintf(numstr, "%d", line);
		line1 = line1 + " - " + source + ":" + numstr;
	}
	
	if(*consoleOut){
#if defined(_WIN64) || defined(_WIN32)
		//Windows specific code
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
		switch (type){
			case INFO: 
				SetConsoleTextAttribute( hstdout, 0x0F );
				break;
			case DEBUG: 
				SetConsoleTextAttribute( hstdout, 0x02 );
				break;
			case WARN:
				SetConsoleTextAttribute( hstdout, 0x06 );
				break;
			case ERR:
				SetConsoleTextAttribute( hstdout, 0x0C );
				break;
		}
		cout << timestamp << line1 << " - " << message << endl;
		//End Windows specific code
#else
		//UNIX specific code
		string colour;
		switch (type){
			case INFO: 
				colour = "\033[0;37m";
				break;
			case DEBUG: 
				colour = "\033[0;32m";
				break;
			case WARN:
				colour = "\033[0;33m";
				break;
			case ERR:
				colour = "\033[0;31m";
				break;
		}
		
		cout << colour << timestamp << line1 << " - " << message << endl;
		//End UNIX specific code
#endif
	}
	if(*fileOut){
		//Output the plain text to the log file
		ofstream logFile;
		logFile.open ("console.log", fstream::out | fstream::app);
		logFile << timestamp << line1 << " - " << message << endl;
		logFile.close();
	}
}

Logger::~Logger() {
}

Logger::Logger(){
	// Set default logging behaviour 
	fileOut = new bool(false);
	consoleOut = new bool(false);
	level = new LOGLEVEL(OFF);
	// Open the log file and make sure it is a new section 
	time_t rawTime;
	struct tm * timeinfo;
	char timestamp [20];
	time(&rawTime);
	timeinfo = localtime (&rawTime);
	strftime (timestamp,30,"%d/%m/%Y %H:%M:%S",timeinfo);
	
	ofstream logFile;
	logFile.open ("console.log", fstream::out | fstream::app);
	logFile << endl ;
	logFile << endl ;
	logFile << "###########################################################################" << endl;
	logFile << "## Space Evaders Console Log     -       " << timestamp << "             ##" << endl;
	logFile << "###########################################################################" << endl;
	logFile << endl;
	logFile.close();
}

Logger* Logger::getInstance(){
	if(pLogger == NULL){
		pLogger = new Logger();
	}
	return pLogger;
}
