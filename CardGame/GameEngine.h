#pragma once
#include "GameComponents.h"
#include "GameStateManager.h"
#include "RulesManager.h"

class GameEngine {
public:
	GameEngine();
	~GameEngine();

	GameComponents gameComponents;

	RulesManager rulesManager{gameComponents};

	GameStateManager gameStateManager{gameComponents};

	//Updates the GameEngine 
	void update();
};
