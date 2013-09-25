/* 
 * File:   LogHandler.cpp
 * Author: williampoynter
 * 
 * Created on September 25, 2013, 7:36 PM
 */

#include "LogHandler.h"

LogHandler::LogHandler() {
}

LogHandler::LogHandler(const LogHandler& orig) {
        logs = orig.getAllLogs();
}

LogHandler::~LogHandler() {
        logs.clear();
}

std::list<std::string> LogHandler::getAllLogs() const {
        return logs;
}

bool LogHandler::pop(std::string &item) {
        if (logs.empty()) 
                return false;
        item = logs.front();
        logs.pop_front();
        return true;
}

void LogHandler::push(const std::string &item) {
        logs.push_back(item);
}