/* 
 * File:   logger.cpp
 * Author: Robert Parker
 *
 * Created on October 3, 2013, 21:09 PM
 */
 
#include "logger.h"

logger* logger::pLogger = NULL;

using namespace std;

string logger::trim(string line){
	string front = "";
	string back = "";
	bool chars = false;

	//trim front
	for( unsigned int i = 0; i < line.length() ; i++){
		if(((char)line[i] != ' ') || chars){
			chars = true;
			front = front + (char)line[i];
		} else {
			//do nothing as it's a space so we don't want it
		}
	}
	chars = false;
	//If we've trimmed it to nothing return an empty string (blank line of spaces)
	if(front.length()==0){
		return front;
	}
	
	//Trim back, we definitely have chars to hit at this point
	unsigned int i = front.length();
	while((char)front[i-1] == ' '){
		i--;
	}
	//Found where the whitespace stops so copy everything up to there
	for(unsigned int x = 0; x < i ; x++){
		back = back + (char)front[x];
	}

	return back;
}
splitted logger::split(string line, char token){
	splitted back;
	string current = "";
	bool splitted = false;
	for( unsigned int i = 0; i < line.length() ; i++){
		if(!splitted && ((char)line[i] == token)){
			back.key = current;
			current = "";
		} else {
			current = current + line[i];
		}
	}
	back.value = current;
	return back;
}
void logger::changeLogging(bool file, bool console, LOGLEVEL newLevel){
    if(pLogger == NULL){
		//We need to initalise before we change the settings
		pLogger = new logger();
	}
	fileOut = new bool(file);
	consoleOut = new bool(console);
	level = new LOGLEVEL(newLevel);
}

void logger::log(string message, LOGTYPE type){
	if(pLogger == NULL){
		//We need to initalise before we log out first time
		pLogger = new logger();
	} 
	pLogger->log(message, type, "");
}

void logger::log(string message, LOGTYPE type, string source){
	if(pLogger == NULL){
		//We need to initalise before we log out first time
		pLogger = new logger();
	}
	
	// Do first checks to determine if we should log
	if(type == INFO && *level != DEBUG){
		//we do not log out INFO on anything BUT debug
		return;
	} else if(type == WARN && *level == OFF){
		//We only log out on Anything except OFF
		return;
	}
	//We always log out error messages
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
	} else{
		line1 = " - ERR!";
	}
	
	//Finally append the source (if supplied)
	if(source.length() > 0){
		line1 = line1 + " - " + source;
	}
	
	if(*consoleOut){
#if defined(_WIN64) || defined(_WIN32)
		//Windows specific code
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
		switch (type){
			case INFO: 
				SetConsoleTextAttribute( hstdout, 0x0F );
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

logger::~logger() {
}

logger::logger(){
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

logger* logger::getInstance(){
	if(pLogger == NULL){
		pLogger = new logger();
	}
	return pLogger;
}
