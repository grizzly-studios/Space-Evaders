/* 
 * File:   logger.cpp
 * Author: Robert Parker
 *
 * Created on October 3, 2013, 21:09 PM
 */
 
#include "Logger.h"

using namespace gs;

LogBuffer::LogBuffer(std::ostream &_sink) : sink(_sink), isNewLine(true) {
	label = "";
    setp(buf, buf + (bufSize - 1));
}

LogBuffer::LogBuffer(std::ostream &_sink, Color color) : sink(_sink), isNewLine(true) {
	label = "";
	setp(buf, buf + (bufSize - 1));
}

LogBuffer::~LogBuffer() {
	
}

std::string LogBuffer::header() {
	time_t rawTime;
	time(&rawTime);
	std::tm *lTime = std::localtime(&rawTime);
	char timeBuf[100];
	strftime(timeBuf, sizeof(timeBuf), "[%d/%m/%Y %H:%M:%S]", lTime);

	return std::string(timeBuf) + " - " + 
		((label != "") ? (label + " - ") : "" );
}

void LogBuffer::setLabel(std::string _label) {
	label = _label;
}

int LogBuffer::flushBuffer () {
	int num = pptr()-pbase();
	sink.write(buf, num);
	if (sink.eof()) {
		return EOF;
	}
	pbump(-num); // reset put pointer accordingly
	return num;
}

int LogBuffer::overflow(int c = EOF) {
	int result = c;
	if (isNewLine) {
		sink << header();
	}
	if (sink && c != EOF) {
		*pptr() = c;
		pbump(1);
	}

	result = flushBuffer();
	isNewLine = c == '\n';
	return (result == EOF) ? EOF : c;
}

int LogBuffer::sync() {
	sink << std::flush;
	
    return (flushBuffer() == EOF) ? -1 : 0;
}

LogHandler* LogHandler::pLogHandler = NULL;

LogHandler* LogHandler::getInstance() {
	if (pLogHandler == NULL) {
		pLogHandler = new LogHandler();
	}
	return pLogHandler;
}

void LogHandler::log(const std::string& message, LOGTYPE type, const std::string& source, int line) {
	if (pLogHandler == NULL) {
		//We need to initialise before we log out first time
		pLogHandler = new LogHandler();
	}
	
	// Do first checks to determine if we should log
	if (type != ERR_TYPE && level != FULL) {
		//we do not log out INFO, WARN or DEBUG on anything BUT full
		return;
	} 
	
	//Now create the logging message
	std::string line1;

	//Get current date and time
	time_t rawTime;
	struct tm * timeinfo;
	char timestamp [20];
	time(&rawTime);
	timeinfo = localtime (&rawTime);
	strftime (timestamp,30,"%d/%m/%Y %H:%M:%S",timeinfo);
	
	//Sort out string representation of type
	switch (type) {
		case INFO_TYPE:
			line1 = " - INFO";
			break;
		case WARN_TYPE:
			line1 = " - WARN";
			break;
		case ERR_TYPE:
			line1 = " - ERR!";
			break;
		case DEBUG_TYPE:
			line1 = " - DEBUG";
			break;
	}
	
	//Finally append the source (if supplied)
	if (source.length() > 0) {
		char numstr[21];
		sprintf(numstr, "%d", line);
		line1 = line1 + " - " + source + ":" + numstr;
	}
	
	if(consoleOut) {
#if defined(_WIN64) || defined(_WIN32)
		//Windows specific code
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
		switch (type) {
			case INFO_TYPE:
				SetConsoleTextAttribute( hstdout, 0x0F );
				break;
			case DEBUG_TYPE:
				SetConsoleTextAttribute( hstdout, 0x02 );
				break;
			case WARN_TYPE:
				SetConsoleTextAttribute( hstdout, 0x06 );
				break;
			case ERR_TYPE:
				SetConsoleTextAttribute( hstdout, 0x0C );
				break;
		}
		std::cout << timestamp << line1 << " - " << message << std::endl;
		//End Windows specific code
#else
		//UNIX specific code
		std::string colour;
		switch (type) {
			case INFO_TYPE:
				colour = "\033[0;37m";
				break;
			case DEBUG_TYPE:
				colour = "\033[0;32m";
				break;
			case WARN_TYPE:
				colour = "\033[0;33m";
				break;
			case ERR_TYPE:
				colour = "\033[0;31m";
				break;
		}
		
		std::cout << colour << timestamp << line1 << " - " << message << std::endl;
		//End UNIX specific code
#endif
	}
	if (fileOut) {
		//Output the plain text to the log file
		std::ofstream logFile;
		logFile.open ("console.log", std::fstream::out | std::fstream::app);
		logFile << timestamp << line1 << " - " << message << std::endl;
		logFile.close();
	}
}

void LogHandler::changeLogging(bool file, bool console, LOGLEVEL newLevel) {
	if(pLogHandler == NULL) {
		//We need to initalise before we change the settings
		pLogHandler= new LogHandler();
	}
	fileOut = file;
	consoleOut = console;
	level = newLevel;
}

LogHandler::LogHandler() : fileOut(false), consoleOut(false), level(OFF) {
	// Open the log file and make sure it is a new section 
	time_t rawTime;
	struct tm * timeinfo;
	char timestamp [20];
	time(&rawTime);
	timeinfo = localtime (&rawTime);
	strftime (timestamp,30,"%d/%m/%Y %H:%M:%S",timeinfo);
	
	std::ofstream logFile;
	logFile.open ("console.log", std::fstream::out | std::fstream::app);
	logFile << std::endl ;
	logFile << std::endl ;
	logFile << "###########################################################################"
		<< std::endl;
	logFile << "## Space Evaders Console Log     -       " << timestamp << "             ##"
		<< std::endl;
	logFile << "###########################################################################"
		<< std::endl;
	logFile << std::endl;
	logFile.close();
}

LogHandler::~LogHandler() {
}
