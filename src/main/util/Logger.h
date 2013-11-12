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
#define INFO(_msg_) LogHandler::getInstance()->log(_msg_, INFO_TYPE, __FILE__, __LINE__)
#define WARN(_msg_) LogHandler::getInstance()->log(_msg_, WARN_TYPE, __FILE__, __LINE__)
#define ERR(_msg_) LogHandler::getInstance()->log(_msg_, ERR_TYPE, __FILE__, __LINE__)
#define DBG(_msg_) LogHandler::getInstance()->log(_msg_, DEBUG_TYPE, __FILE__, __LINE__)
#define CHANGE_LOG LogHandler::getInstance()->changeLogging

namespace gs {

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

enum Color {
	RED,
	GREEN,
	BLUE,
	YELLOW,
	ORANGE,
	PURPLE,
	PINK,
	BROWN,
	GREY,
	WHITE
};

class LogBuffer : public std::streambuf {
public:
	LogBuffer(std::ostream &_sink);
	LogBuffer(std::ostream &_sink, Color color);
	virtual ~LogBuffer();
protected:
	static const int bufSize = 1;
	char buf[bufSize];
	std::string label;
	std::ostream &sink;
	bool isNewLine;
private:
	std::string header();
	void setLabel(std::string);
	int flushBuffer();
	virtual int overflow (int c);
	virtual int sync();
};

class Logger : public std::ostream {
public:
	Logger(LogType _type, std::ostream &_sink = std::cout);
	Logger(LogType _type, Color _color, std::ostream &_sink = std::cout);
	virtual ~Logger();
private:
	LogType type;
	Color color;
};

class LogHeader {
public:
	LogHeader();
	virtual ~LogHeader();
	
	void addLogger(LogType _type, std::ostream &_sink);
	void clearLoggers();
	
	friend std::ostream& operator<< (std::ostream &out, LogHeader &logHeader);
private:
	std::list<Logger*> loggers;
};
	
class LogHandler {
public:
	static LogHandler* getInstance();
	void changeLogging(bool file, bool console, LogLevel newLevel);

private:
	LogHandler();
	virtual ~LogHandler();

	static LogHandler* pLogHandler;
	LogHeader warningLogHeader;
	LogHeader errorLogHeader;
	LogHeader infoLogHeader;
	LogHeader debugLogHeader;
	
	bool initalised;
	bool fileOut;
	bool consoleOut;
	LogLevel level;
	std::ofstream logFile;
};

}

#endif	/* LOGGER_H */
