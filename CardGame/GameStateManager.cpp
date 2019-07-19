#include "GameStateManager.h"

GameStateManager::GameStateManager(GameComponents &components) : gameComponents(components) {
	turnCycle.push_back(std::make_unique<StandardGamePhases::GamePhase_Draw>(StandardGamePhases::GamePhase_Draw(gameComponents))); //Add draw phase to turn cycle
	turnCycle.push_back(std::make_unique<StandardGamePhases::GamePhase_Planning>(StandardGamePhases::GamePhase_Planning(gameComponents))); //Add planning phase to turn cycle
	turnCycle.push_back(std::make_unique<StandardGamePhases::GamePhase_Action>(StandardGamePhases::GamePhase_Action(gameComponents))); //Add action phase to turn cycle
}

GameStateManager::~GameStateManager() {}

void GameStateManager::reset() {
}

void GameStateManager::newGame() {
	
}

void GameStateManager::updatePhase() {
	(**currentPhase).update();
}

void GameStateManager::nextPhase() {
	if (currentPhase != turnCycle.end()) {
		++currentPhase;
	}
	else {
		currentPhase = turnCycle.begin();
	}
}

void GameStateManager::update() {
	if ((**currentPhase).isFinished()) {
		nextPhase();
	}
	updatePhase();
}