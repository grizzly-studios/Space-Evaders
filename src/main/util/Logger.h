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
#include <sstream>
#include <list>

//MACRO definitions
#define INFO LogHandler::getInstance()->infoLog << __FILE__ << ":" << __LINE__ << " - " << LogBuffer::getColor(WHITE)
#define WARN LogHandler::getInstance()->warningLog << __FILE__ << ":" << __LINE__ << " - " << LogBuffer::getColor(YELLOW)
#define ERR LogHandler::getInstance()->errorLog << __FILE__ << ":" << __LINE__ << " - " << LogBuffer::getColor(RED)
#define DBG LogHandler::getInstance()->debugLog << __FILE__ << ":" << __LINE__ << " - " << LogBuffer::getColor(GREEN)

namespace gs {

const std::string defaultFileName = "console.log";

enum LogLevel {
	OFF,
	DEFAULT,
	FULL
};

enum LogType {
	INFO_TYPE,
	WARN_TYPE,
	ERR_TYPE,
	DEBUG_TYPE
};

enum LogColor {
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	PINK,
	BROWN,
	GREY,
	WHITE,
	BLACK,
	RESET
};

enum LogOutput {
	NO_OUTPUT,
	CONSOLE,
	FILE,
	BOTH
};

class LogBuffer : public std::streambuf {
public:
	LogBuffer(LogOutput _output, LogType type);
	LogBuffer(LogOutput _output, LogType type, LogColor _color);
	virtual ~LogBuffer();
	
	std::string getColor();
	static std::string getColor(LogColor _color, bool bold = false);
	void setColor(LogColor _color);
	void setOutput(LogOutput _output);
	void setType(LogType type);
	
protected:
	static const int bufSize = 1;
	char buf[bufSize];
	std::string label;
	LogColor color;
	LogOutput output;
	std::ostream &screenSink;
	std::ofstream fileSink;
	bool isNewLine;
	
	std::string header();
	void setLabel(std::string);
	int flushBuffer();
	
private:
	virtual int overflow (int c);
	virtual int sync();
};

class Logger : public std::ostream {
public:
	Logger(LogOutput _output, LogType _type);
	Logger(LogOutput _output, LogType _type, LogColor _color);
	virtual ~Logger();
	
	void setOutput(LogOutput _output);
	void setColor(LogColor _color);
	void setType(LogType type);
private:
};
	
class LogHandler {
public:
	static LogHandler* getInstance();
	
	Logger warningLog;
	Logger errorLog;
	Logger infoLog;
	Logger debugLog;

private:
	LogHandler();
	virtual ~LogHandler();

	static LogHandler* pLogHandler;
	
	std::ofstream logFile;
};

}

#endif	/* LOGGER_H */
