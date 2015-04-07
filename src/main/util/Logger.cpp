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
			break;
		case ERR_TYPE:
			label = "ERROR";
			color = RED;
			break;
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
			break;
		case ERR_TYPE:
			label = "ERROR";
			break;
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

std::string LogBuffer::getColor(LogColor _color, bool bold) {
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
			SetConsoleTextAttribute(hstdout, LogHandler::getInstance()->getOriginalColor());
			break;
	}
	return "";
	#else
	std::string boldBit = bold ? "1" : "0";
	switch (_color) {
		case RED:
			return "\033["+boldBit+";91m";
		case GREEN:
			return "\033["+boldBit+";32m";
		case BLUE:
			return "\033["+boldBit+";94m";
		case YELLOW:
			return "\033["+boldBit+";93m";
		case PURPLE:
			return "\033["+boldBit+";35m";
		case PINK:
			return "\033["+boldBit+";95m";
		case BROWN:
			return "\033["+boldBit+";31m";
			break;
		case GREY:
			return "\033["+boldBit+";90m";
			break;
		case WHITE:
			return "\033["+boldBit+";97;40m";
			break;
		case BLACK:
			return "\033["+boldBit+";30;47m";
			break;
		case RESET:
			return "\033["+boldBit+";39;49m";
			
	}
	#endif
}

std::string LogBuffer::header() {
	time_t rawTime;
	time(&rawTime);
	tm *lTime = localtime(&rawTime);
	char timeBuf[100];
	strftime(timeBuf, sizeof(timeBuf), "[%d/%m/%Y %H:%M:%S]", lTime);

	return getColor(color, true) + std::string(timeBuf) + " - " + 
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

void LogBuffer::setColor(LogColor _color) {
	color = _color;
}

void LogBuffer::setOutput(LogOutput _output) {
	output = _output;
}

void LogBuffer::setType(LogType type) {
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

void Logger::setOutput(LogOutput _output) {
	LogBuffer *buf = static_cast<LogBuffer *>(rdbuf());
	buf->setOutput(_output);
}

void Logger::setColor(LogColor _color) {
	LogBuffer *buf = static_cast<LogBuffer *>(rdbuf());
	buf->setColor(_color);
}

void Logger::setType(LogType _type) {
	LogBuffer *buf = static_cast<LogBuffer *>(rdbuf());
	buf->setType(_type);
}

LogHandler* LogHandler::pLogHandler = NULL;

LogHandler* LogHandler::getInstance() {
	if (pLogHandler == NULL) {
		pLogHandler = new LogHandler();
	}
	return pLogHandler;
}

LogHandler::LogHandler() : 
	warningLog(NO_OUTPUT, WARN_TYPE),
	errorLog(NO_OUTPUT, ERR_TYPE),
	infoLog(NO_OUTPUT, INFO_TYPE),
	debugLog(NO_OUTPUT, DEBUG_TYPE) {

#if defined(_WIN64) || defined(_WIN32)
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hstdout, &info);
	OriginalColors = info.wAttributes;
	SetConsoleTextAttribute(hstdout, 15);
#endif

}

LogHandler::~LogHandler() {
#if defined(_WIN64) || defined(_WIN32)	
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute(hstdout, OriginalColors);
#endif
}

#if defined(_WIN64) || defined(_WIN32)
short LogHandler::getOriginalColor(){
	return OriginalColors;
}
#endif
