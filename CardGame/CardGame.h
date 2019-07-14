#pragma once
#include <SFML/Window.hpp>

class CardGame
{

public:
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

	sf::Window windowHandle;
	
	//Passing false will close the program via breaking of the main program loop
	void setRunning(bool running);

	//Returns a handle for the main program window.
	sf::Window &getMainWindow();

	//Creates and initializs the main program window.
	void initializeMainWindow();

	//Updates the main program window
	void updateWindow();
};