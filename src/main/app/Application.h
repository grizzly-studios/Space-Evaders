/* 
 * File:   Application.h
 * Author: williampoynter
 *
 * Created on September 25, 2013, 1:11 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <tr1/memory>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../event/EventManager.h"
#include "../event/GameStateChangedEvent.h"

#include "../logic/Logic.h"

#include "../view/View.h"
#include "../view/KeyboardListener.h"
#include "../view/UserInput.h"

namespace gs {

typedef std::tr1::shared_ptr<sf::RenderWindow> RenderWindowShPtr;

/**
 * Application layer implementation
 * 
 * The Application object is the highest level object to be created. It handles the entire program
 * and houses the Event Manager, Logic and View. It also takes care of a number of other running
 * preferences.
 * 
 */
class Application {
public:
	/**
	 * Constructor
	 * 
	 * This is the only constructor for the Application. It requires the passing of the program
	 * arguments from the terminal.
     * @param argc Number of arguments being passed
     * @param argv An array of arguments
     */
	Application(int argc, char** argv);
	/**
	 * Destructor
     */
	virtual ~Application();
	/**
	 * Initialise Application
	 * 
	 * Prepares the Application for running by creating the View, Logic and Event Manger and
	 * performing startup tasks.
     */
	void init();
	/**
	 * Run Application
	 * 
	 * Handles the program kernel.
     */
	void run();

private:
	/**Shared pointer to Event Manager*/
	IEventManagerPtr eventManager;
	/**Shared pointer to Logic*/
	ILogicPtr logic;
	/**Shared pointer to View*/
	IViewPtr view;
	/**Boolean to indicate forced log flushing*/
	bool flush;
	/**Screen frame rate*/
	unsigned int FR;
	/**Antialiasing level*/
	unsigned int AL;
	/**Screen width and height*/
	unsigned int WIDTH, HEIGHT;
	/**SFML settings for render window*/
	sf::ContextSettings settings;
	/**Shared pointer to render window*/
	RenderWindowShPtr window;
};

}

#endif	/* APPLICATION_H */

