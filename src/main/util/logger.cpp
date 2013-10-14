/* 
 * File:   logger.cpp
 * Author: Robert Parker
 *
 * Created on October 3, 2013, 21:09 PM
 */
 
#include "logger.h"

logger* logger::pLogger = NULL;

using namespace std;

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
		pLogger->readPropertiesFile();
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
	
	if(*consoleOut){
		std::cout << message << std::endl;
	}
	if(*fileOut){
		//Nothing for now
	}
}

logger::~logger() {
}

logger::logger(){
	// Set default logging behaviour 
	fileOut = new bool(false);
	consoleOut = new bool(false);
	level = new LOGLEVEL(OFF);
}

void logger::readPropertiesFile(){
	// We look for a properties file, if it exists we override the defaults 
	ifstream propFile;
	string line;
	propFile.open ("logging.properties");
	if(propFile.is_open()){
		
		splitted property;
		// File exists and is open for reading
		while(!propFile.eof()){
			getline(propFile, line);
			if(line[0] == '#' || line.length() == 0){
				// comment, blank line so continue
				continue;
			}
			property = split(line, '=');
			// Now we have the property, let's work out which it is then set it 
			if(property.key.compare("level")==0){
				if(property.value.compare("off")==0){
					level = new LOGLEVEL(OFF);
				} else if(property.value.compare("standard")==0){
					level = new LOGLEVEL(STANDARD);
				} else if(property.value.compare("debug")==0){
					level = new LOGLEVEL(DEBUG);
				} else{
					log("Unknown value: " + property.value + " given for key: " + property.key, ERROR);
				}
			} else if(property.key.compare("output")==0){
				if(property.value.compare("off")==0){
					fileOut = new bool(false);
					consoleOut = new bool(false);
				} else if(property.value.compare("file")==0){
					fileOut = new bool(true);
					consoleOut = new bool(false);
				} else if(property.value.compare("console")==0){
					fileOut = new bool(false);
					consoleOut = new bool(true);
				} else if(property.value.compare("both")==0){
					fileOut = new bool(true);
					consoleOut = new bool(true);
				} else{
					log("Unknown value: " + property.value + " given for key: " + property.key, ERROR);
				}
			} else{
				// Fuck knows what they gave us, output and move on 
				log("Unknown property: " + line, ERROR);
			}
		
		}
		log("Finished reading properties file",INFO); //No point in INFO or WARN messages before this point
		propFile.close();
	} else {
		//log("No property file found, using defaults", WARN);
	}
}

logger* logger::getInstance(){
	if(pLogger == NULL){
		pLogger = new logger();
		pLogger->readPropertiesFile(); //No point in INFO or WARN messages before this point
	}
	return pLogger;
}
