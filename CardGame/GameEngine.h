#pragma once
#include "GameComponents.h"
#include "GameStateManager.h"
#include "RulesManager.h"
#include "PhaseCycle.h"

class GameEngine {
public:
	GameEngine();
	~GameEngine();

	GameComponents gameComponents;
	PhaseCycle phaseCycle;

	RulesManager rulesManager{gameComponents, phaseCycle};

	GameStateManager gameStateManager{gameComponents, phaseCycle};

	//Updates the GameEngine 
	void update();
};
