#pragma once
#include "GameComponents.h"
#include "GameStateManager.h"
#include "RulesManager.h"
#include "Player.h"
#include "Opponent.h"
#include "Field.h"

class GameEngine {
public:
	GameComponents gameComponents;

	GameStateManager gameStateManager{gameComponents};
	RulesManager rulesManager{gameComponents};

	~GameEngine();

	static GameEngine &instance();

private:
	//TODO Reasonably has no business being a singleton

	GameEngine();
	GameEngine(const GameEngine&) = delete;
	GameEngine(GameEngine&&) = delete;
	GameEngine &operator = (const GameEngine&) = delete;
	GameEngine &operator = (GameEngine&&) = delete;
};
