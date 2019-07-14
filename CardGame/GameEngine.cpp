#include "GameEngine.h"

GameEngine::GameEngine() {}

GameEngine &GameEngine::instance() {
	static GameEngine instance;
	return instance;
}

GameEngine::~GameEngine() {}