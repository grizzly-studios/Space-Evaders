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
#define INFO LogHandler::getInstance()->infoLog << __FILE__ << ":" \
	<< __LINE__ << " - " << LogBuffer::getColor(WHITE)
#define WARN LogHandler::getInstance()->warningLog << __FILE__ << ":" \
	<< __LINE__ << " - " << LogBuffer::getColor(YELLOW)
#define ERR LogHandler::getInstance()->errorLog << __FILE__ << ":" \
	<< __LINE__ << " - " << LogBuffer::getColor(RED)
#define DBG LogHandler::getInstance()->debugLog << __FILE__ << ":" \
	<< __LINE__ << " - " << LogBuffer::getColor(GREEN)

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

/**
 * Stream buffer to be used for the logging
 */
class LogBuffer : public std::streambuf {
public:
	/** Constructor
	 * 
	 * The constructor generates the correct labeling for logging from the log type. The internal 
	 * buffer pointer is also set.
	 * 
     * @param _output Specifies locations to logout to
     * @param type Log type
     */
	LogBuffer(LogOutput _output, LogType type);
	/** Constructor
	 * 
	 * The constructor generates the correct labeling for logging from the log type. The internal 
	 * buffer pointer is also set.
	 * 
	 * @param _output Specifies locations to logout to
	 * @param type Log type
     * @param _color Font color for logging to console
     */
	LogBuffer(LogOutput _output, LogType type, LogColor _color);
	/** Destructor
	 * 
	 * Closes output file, if one is open.
	 */
	virtual ~LogBuffer();
	/** Returns the ANSI string required to color the output to console
	 * 
	 * This function also calls the WIN32/64 command needed to color the output to console.
	 */
	std::string getColor();
	static std::string getColor(LogColor _color, bool bold = false);
	/** Sets the color to be used by this buffer
	 * 
     * @param _color New color
     */
	void setColor(LogColor _color);
	/** Set the output to be used by this buffer
	 * 
	 * @param _output Specifies locations to logout to
     */
	void setOutput(LogOutput _output);
	/** Set the log type
	 * 
     * @param type Log type
     */
	void setType(LogType type);
	
protected:
	/** Buffer size */
	static const int bufSize = 1;
	/** Output buffer */
	char buf[bufSize];
	/** Output type label */
	std::string label;
	/** Output font color */
	LogColor color;
	/** Output locations */
	LogOutput output;
	/** Console output stream */
	std::ostream &screenSink;
	/** File output stream */
	std::ofstream fileSink;
	/** Denotes whether the next character is a new line */
	bool isNewLine;
	/** Generates the formatted date and time header for each line
	 * 
     * @return Formatted header string containing time and date
     */
	std::string header();
	/** Sets line labeling 
	 * 
     * @param New label
     */
	void setLabel(std::string);
	/** Flushes the streambuf into the output buffers
	 * 
     * @return Number of characters written to the output buffers or EOF if the streambuf is empty
     */
	int flushBuffer();
	
private:
	/** Virtual function to be used internally to place a character in the overflow
	 * 
     * @param c Character to add
     * @return In success the character is returned otherwise an EOF is returned
     */
	virtual int overflow (int c);
	/** Synchronise stream buffer
	 * 
     * @return In success returns 0 or -1 on failure
     */
	virtual int sync();

};
/** Logging output stream */
class Logger : public std::ostream {
public:
	/** Constructor
	 * 
     * @param _output Specifies locations to logout to
     * @param _type Log type
     */
	Logger(LogOutput _output, LogType _type);
	/**
     * @param _color Font color for logging to console
     */
	Logger(LogOutput _output, LogType _type, LogColor _color);
	/**
	 * Destructor
	 */
	virtual ~Logger();
	/** Set output locations
	 * 
     * @param _output New output locations
     */
	void setOutput(LogOutput _output);
	/** Set output font color
	 * 
     * @param _color New font color
     */
	void setColor(LogColor _color);
	/** Set output type
	 * 
	 * This then sets the output labeling
	 * 
     * @param type New type
     */
	void setType(LogType type);
};
/** Log Handler Singleton */
class LogHandler {
public:
	/** Gets instance of singleton
	 * 
	 * @return Pointer to this singleton
	 */
	static LogHandler* getInstance();
	/** Warning output log stream */
	Logger warningLog;
	/** Error output log stream */
	Logger errorLog;
	/** Info output log stream */
	Logger infoLog;
	/** Debug output log stream */
	Logger debugLog;

#if defined(_WIN64) || defined(_WIN32)
	/* Only in the windows code */
	short getOriginalColor();
#endif

private:
	/** Constructor */
	LogHandler();
	/** Destructor */
	virtual ~LogHandler();
	/** Pointer to this singleton */
	static LogHandler* pLogHandler;

#if defined(_WIN64) || defined(_WIN32)
	/* Only in the windows code */
	short OriginalColors;
#endif
};

}



#endif	/* LOGGER_H */
