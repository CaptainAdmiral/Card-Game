#include "CardGame.h"

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
	return getMainWindow().create(sf::VideoMode(Settings::getSettings().DEFAULT_WIDTH, Settings::getSettings().DEFAULT_HEIGHT), "Card Game");
}

void CardGame::initializeGraphics() {
	RenderManager::instance().setWindow(windowHandle);
}

void CardGame::updateWindow() {
	sf::Event event;
	sf::RenderWindow &window = getMainWindow();
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			getMainWindow().close();
			CardGame::close();
		}
		window.clear();
		updateGraphics();
		window.display();
	}
}

void CardGame::updateGame() {
	gameEngine.update();
}

void CardGame::updateGraphics() {
	RenderManager::instance().doRender();
}

void CardGame::initialize() {
	if(!DEBUG) ShowWindow(GetConsoleWindow(), 0);

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
	CardGame &instance = CardGame::instance();
	
	//Initialization
	instance.initialize();

	//Main program loop
	while (instance.getRunning()) {
		instance.update();
	}

	return 0;
}