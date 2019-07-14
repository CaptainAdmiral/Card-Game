#include "GameStateManager.h"

GameStateManager::GameStateManager(GameComponents &gameComponents) {}

GameStateManager::~GameStateManager() {}

void GameStateManager::reset() {
}

void GameStateManager::newGame() {
}

void GameStateManager::updatePhaseState() {
	
}

void GameStateManager::doPhase() {
	state->doPhase();
}

void GameStateManager::nextPhase() {
	static_cast<GamePhase>(static_cast<int>(phase)+1); //TODO implement method that respects the non contiguousness and descreteness of enum
}

void GameStateManager::update() {}