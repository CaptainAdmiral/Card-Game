#pragma once
//TODO remove platform dependancy
#include <SFML/Graphics.hpp>
#include <windows.h>

#include "RenderManager.h"
#include "GameEngine.h"
#include "Settings.h"

class CardGame
{

public:
	GameEngine gameEngine;

	~CardGame();

	//Returns CardGame's singleton instance
	static CardGame &instance();
	
	bool getRunning() const;
	
	//Exit's the main program loop
	void close();

	//Initialization
	void initialize();

	//The main program loop
	void update();

private:
	CardGame();
	CardGame(const CardGame&) = delete;
	CardGame(CardGame&&) = delete;
	CardGame &operator = (const CardGame&) = delete;
	CardGame &operator = (CardGame&&) = delete;

	bool isRunning;

	sf::RenderWindow windowHandle;
	
	//Passing false will close the program via breaking of the main program loop
	void setRunning(bool running);

	//Returns a handle for the main program window.
	sf::RenderWindow &getMainWindow();

	//Creates and initializs the main program window.
	void initializeMainWindow();

	//Initializes the graphics engine
	void initializeGraphics();

	//Updates the main program window
	void updateWindow();

	//Temp function in place of broader logic update
	void updateGame();

	//Iterates through the render manager render list
	void updateGraphics();
};