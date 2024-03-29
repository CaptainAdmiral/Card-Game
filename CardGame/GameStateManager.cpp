#include "GameStateManager.h"
#include "PhaseCycle.h"
#include "StandardGamePhases.h"
#include "GamePhasePlanning.h"
#include "GamePhaseAction.h"

GameStateManager::GameStateManager(GameComponents &components, PhaseCycle &cycle) : gameComponents(components), cycle(cycle) {
	cycle.phaseVec.push_back(std::make_unique<StandardGamePhases::Start>(gameComponents, &gameComponents.player, &cycle)); //Add player 1 setup and initial draw phase to the turn cycle
	cycle.phaseVec.push_back(std::make_unique<StandardGamePhases::Start>(gameComponents, &gameComponents.player2, &cycle)); //Add player 2 setup and initial draw phase to the turn cycle
	cycle.phaseVec.push_back(std::make_unique<StandardGamePhases::Draw>(gameComponents, &gameComponents.player)); //Add player 1 draw phase to turn cycle
	cycle.phaseVec.push_back(std::make_unique<StandardGamePhases::Draw>(gameComponents, &gameComponents.player2)); //Add player 2 draw phase to turn cycle
	cycle.phaseVec.emplace_back(new GamePhasePlanning(gameComponents, &gameComponents.player, &cycle)); //Add player 1 planning phase to turn cycle
	cycle.phaseVec.emplace_back(new GamePhasePlanning(gameComponents, &gameComponents.player2, &cycle)); //Add player 2 planning phase to turn cycle
	cycle.phaseVec.push_back(std::make_unique<GamePhaseAction>(gameComponents)); //Add action phase to turn cycle

	cycle.currentPhase = cycle.phaseVec.begin();
}

GameStateManager::~GameStateManager() {}

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