/* 
 * File:   LogHandler.h
 * Author: williampoynter
 *
 * Created on September 25, 2013, 7:36 PM
 */

#ifndef LOGHANDLER_H
#define	LOGHANDLER_H

#include <list>
#include <string>

class LogHandler {
public:
        LogHandler();
        LogHandler(const LogHandler& orig);
        virtual ~LogHandler();
        
        std::list<std::string> getAllLogs() const;
        bool pop(std::string &item);
        void push(const std::string &item);
        
private:
        std::list<std::string> logs;

};

#endif	/* LOGHANDLER_H */

