#include "GameStateManager.h"

GameStateManager::GameStateManager(GameComponents &components) : gameComponents(components) {
	cycle.phaseVec.push_back(std::make_unique<StandardGamePhases::GamePhase_Start>(gameComponents, &cycle)); //Add setup and initial draw phase to the turn cycle
	cycle.phaseVec.push_back(std::make_unique<StandardGamePhases::GamePhase_Draw>(gameComponents)); //Add draw phase to turn cycle
	cycle.phaseVec.push_back(std::make_unique<StandardGamePhases::GamePhase_Planning>(StandardGamePhases::GamePhase_Planning(gameComponents))); //Add planning phase to turn cycle
	cycle.phaseVec.push_back(std::make_unique<StandardGamePhases::GamePhase_Action>(StandardGamePhases::GamePhase_Action(gameComponents))); //Add action phase to turn cycle

	cycle.currentPhase = cycle.phaseVec.begin();
}

GameStateManager::~GameStateManager() {}

void GameStateManager::reset() {
}

void GameStateManager::newGame() {
	
}

void GameStateManager::updatePhase() {
	(**cycle.currentPhase).update();
}

void GameStateManager::nextPhase() {
	if (cycle.currentPhase != cycle.phaseVec.end()) {
		++cycle.currentPhase;
	}
	else {
		cycle.currentPhase = cycle.phaseVec.begin();
	}
}

void GameStateManager::update() {
	if ((**cycle.currentPhase).isFinished()) {
		(**cycle.currentPhase).finished = false;
		nextPhase();
	}
	updatePhase();
}