#include "CardGame.h"
#include "Settings.h"
#include "RenderManager.h"
#include "MouseHandler.h"
#include <windows.h>

CardGame::CardGame() {
	setRunning(true);
}

CardGame::~CardGame() {}

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

sf::RenderWindow &CardGame::getMainWindow() {
	return windowHandle;
}

void CardGame::initializeMainWindow() {
	return getMainWindow().create(sf::VideoMode(Settings::General::DEFAULT_WIDTH, Settings::General::DEFAULT_HEIGHT), "Card Game");
}

void CardGame::initializeGraphics() {
	RenderManager::instance().setWindow(windowHandle);
}

void CardGame::updateWindow() {
	sf::RenderWindow &window = getMainWindow();

	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			getMainWindow().close();
			CardGame::close();
		}

		if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased || event.type == sf::Event::MouseMoved) {
			MouseHandler::postEvent(event);
		}
	}

	window.clear();
	updateGraphics();
	window.display();
}

void CardGame::updateGame() {
	gameEngine.update();
}

void CardGame::updateGraphics() {
	RenderManager::instance().doRender();
}

void CardGame::initialize() {
	if(!Settings::Debug::DEBUG) ShowWindow(GetConsoleWindow(), 0);

	initializeMainWindow();
	getMainWindow().setVerticalSyncEnabled(true);

	initializeGraphics();
}

void CardGame::update() {
	updateWindow();
	updateGame();
}








//Main Program Loop
int main() {
	srand(time(NULL));

	CardGame &instance = CardGame::instance();
	
	//Initialization
	instance.initialize();

	//Main program loop
	while (instance.getRunning()) {
		instance.update();
	}

	return 0;
}