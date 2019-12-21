#include "GameEngine.h"

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {}

void GameEngine::update() {
	gameStateManager.update();
}