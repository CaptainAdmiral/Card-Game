#pragma once
#include "GameComponents.h"
#include "GameStateManager.h"
#include "RulesManager.h"

class GameEngine {
public:
	GameEngine();
	~GameEngine();

	GameComponents gameComponents;

	GameStateManager gameStateManager{gameComponents};
	RulesManager rulesManager{gameComponents};
};
