#include "CardGame.h"
//TODO remove platfrom dependancy
#include <windows.h>
#include <SFML/Window.hpp>

CardGame::CardGame() {
	setRunning(true);
}

CardGame &CardGame::instance() {
	static CardGame instance;
	return instance;
}

bool CardGame::getRunning() const{
	return isRunning;
}

void CardGame::setRunning(bool running) {
	isRunning = running;
}

void CardGame::close() {
	setRunning(false);
}

sf::Window &CardGame::getMainWindow() {
	return windowHandle;
}

void CardGame::initializeMainWindow() {
	return getMainWindow().create(sf::VideoMode(500, 500), "Card Game");
}

void CardGame::updateWindow() {
	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	sf::Window &window = getMainWindow();
	while (window.pollEvent(event)) {
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed) {
			getMainWindow().close();
			CardGame::close();
		}
		window.display();
	}
}

void CardGame::initialize() {
	CardGame &instance = CardGame::instance();
	ShowWindow(GetConsoleWindow(), 0);

	instance.initializeMainWindow();
	instance.getMainWindow().setVerticalSyncEnabled(true);
}

void CardGame::update() {
	CardGame::instance().updateWindow();
}

int main() {
	CardGame &instance = CardGame::instance();
	
	//Initialization
	instance.initialize();

	//Main program loop
	while (instance.getRunning()) {
		instance.update();
	}

	return 0;
}

CardGame::~CardGame() {}