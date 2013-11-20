/* 
 * File:   logger.cpp
 * Author: Robert Parker
 *
 * Created on October 3, 2013, 21:09 PM
 */

#include "Logger.h"

using namespace gs;

LogBuffer::LogBuffer(LogOutput _output, LogType type) : 
	output(_output),
	screenSink(std::cout), 
	fileSink(defaultFileName, std::ofstream::app),
	isNewLine(true) {
	
	switch(type) {
		case INFO_TYPE:
			label = "INFO";
			color = WHITE;
			break;
		case WARN_TYPE:
			label = "WARN";
			color = YELLOW;
		case ERR_TYPE:
			label = "ERROR";
			color = RED;
		case DEBUG_TYPE:
			label = "DBG";
			color = GREEN;
			break;
	}
    setp(buf, buf + (bufSize - 1));
}

LogBuffer::LogBuffer(LogOutput _output, LogType type, LogColor _color) : 
	color(_color), 
	output(_output),
	screenSink(std::cout), 
	fileSink(defaultFileName, std::ofstream::app),
	isNewLine(true) {
	
	switch(type) {
		case INFO_TYPE:
			label = "INFO";
			break;
		case WARN_TYPE:
			label = "WARN";
		case ERR_TYPE:
			label = "ERROR";
		case DEBUG_TYPE:
			label = "DBG";
			break;
	}
	setp(buf, buf + (bufSize - 1));
}

LogBuffer::~LogBuffer() {
	if (fileSink.is_open()) {
		fileSink.close();
	}
}

std::string LogBuffer::getColor() {
	return getColor(color);
}

std::string LogBuffer::getColor(LogColor _color) {
	#if defined(_WIN64) || defined(_WIN32)
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	switch (_color) {
		case RED:
			SetConsoleTextAttribute(hstdout, 4);
			break;
		case GREEN:
			SetConsoleTextAttribute(hstdout, 2);
			break;
		case BLUE:
			SetConsoleTextAttribute(hstdout, 1);
			break;
		case YELLOW:
			SetConsoleTextAttribute(hstdout, 14);
			break;
		case PURPLE:
			SetConsoleTextAttribute(hstdout, 5);
			break;
		case PINK:
			SetConsoleTextAttribute(hstdout, 15);
			break;
		case BROWN:
			SetConsoleTextAttribute(hstdout, 6);
			break;
		case GREY:
			SetConsoleTextAttribute(hstdout, 8);
			break;
		case WHITE:
			SetConsoleTextAttribute(hstdout, 15);
			break;
		case BLACK:
			SetConsoleTextAttribute(hstdout, 0);
			break;
		case RESET:
			SetConsoleTextAttribute(hstdout, OriginalColors);
			break;
	}
	return "";
	#else
	switch (_color) {
		case RED:
			return "\033[1;91m";
		case GREEN:
			return "\033[1;32m";
		case BLUE:
			return "\033[1;94m";
		case YELLOW:
			return "\033[1;93m";
		case PURPLE:
			return "\033[1;35m";
		case PINK:
			return "\033[1;95m";
		case BROWN:
			return "\033[1;31m";
			break;
		case GREY:
			return "\033[1;90m";
			break;
		case WHITE:
			return "\033[1;97;40m";
			break;
		case BLACK:
			return "\033[1;30;47m";
			break;
		case RESET:
			return "\033[1;39;49m";
			
	}
	#endif
}

std::string LogBuffer::header() {
	time_t rawTime;
	time(&rawTime);
	std::tm *lTime = std::localtime(&rawTime);
	char timeBuf[100];
	strftime(timeBuf, sizeof(timeBuf), "[%d/%m/%Y %H:%M:%S]", lTime);

	return getColor() + std::string(timeBuf) + " - " + 
		((label != "") ? (label + " - ") : "" );
}

void LogBuffer::setLabel(std::string _label) {
	label = _label;
}

int LogBuffer::flushBuffer () {
	int num = pptr()-pbase();
	if (output == CONSOLE || output == BOTH) {
		screenSink.write(buf, num);
	}
	if (output == FILE || output == BOTH) {
		fileSink.write(buf, num);
	}
	if (screenSink.eof() && fileSink.eof()) {
		return EOF;
	}
	pbump(-num); // reset put pointer accordingly
	return num;
}

int LogBuffer::overflow(int c = EOF) {
	int result = c;
	if (isNewLine) {
		if (output == CONSOLE || output == BOTH) {
			screenSink << header();
		} 
		if (output == FILE || output == BOTH) {
			fileSink << header();
		}
	}
	if (c != EOF) {
		*pptr() = c;
		pbump(1);
	}

	result = flushBuffer();
	isNewLine = c == '\n';
	if (isNewLine) {
		screenSink << getColor(RESET);
		fileSink << getColor(RESET);
	}
	return (result == EOF) ? EOF : c;
}

int LogBuffer::sync() {
	if (output == CONSOLE || output == BOTH) {
			screenSink << std::flush;
		} 
		if (output == FILE || output == BOTH) {
			fileSink << std::flush;
		}
	
    return (flushBuffer() == EOF) ? -1 : 0;
}

Logger::Logger(LogOutput _output, LogType _type) :  
	std::ios(0),
	std::ostream(new LogBuffer(_output, _type))
	{}

Logger::Logger(LogOutput _output, LogType _type, LogColor _color) : 
	std::ios(0),
	std::ostream(new LogBuffer(_output, _type, _color))
	{}

Logger::~Logger() {
	
}

LogHandler* LogHandler::pLogHandler = NULL;

LogHandler* LogHandler::getInstance() {
	if (pLogHandler == NULL) {
		pLogHandler = new LogHandler();
	}
	return pLogHandler;
}

/*void LogHandler::log(const std::string& message, LogType type, const std::string& source, int line) {
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
}*/

LogHandler::LogHandler() : 
	warningLog(BOTH, WARN_TYPE),
	errorLog(BOTH, ERR_TYPE),
	infoLog(BOTH, INFO_TYPE),
	debugLog(BOTH, DEBUG_TYPE),
	fileOut(false), 
	consoleOut(true), 
	level(DEFAULT) {
	
	
	
	/*std::ofstream logFile;
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
	logFile.close();*/
}

LogHandler::~LogHandler() {
}
