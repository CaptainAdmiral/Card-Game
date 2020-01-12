#include "GameStateManager.h"
#include "PhaseCycle.h"

GameStateManager::GameStateManager(GameComponents &components, PhaseCycle &cycle) : gameComponents(components), cycle(cycle) {
	cycle.phaseVec.push_back(std::make_unique<StandardGamePhases::GamePhase_Start>(gameComponents, &cycle)); //Add setup and initial draw phase to the turn cycle
	cycle.phaseVec.push_back(std::make_unique<StandardGamePhases::GamePhase_Draw>(gameComponents)); //Add draw phase to turn cycle
	cycle.phaseVec.emplace_back(new StandardGamePhases::GamePhase_Planning(gameComponents, &cycle)); //Add planning phase to turn cycle
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

void GameStateManager::update() {
	if ((**cycle.currentPhase).isFinished()) {
		(**cycle.currentPhase).finished = false;
		cycle.nextPhase();
	}
	updatePhase();
}