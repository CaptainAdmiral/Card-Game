#pragma once
#include "StandardGamePhases.h"
#include <memory>

class GameStateManager {
public:
	GamePhase phase = GamePhase::BEGIN;

	GameStateManager(GameComponents&);
	~GameStateManager();

	//Resets the game engine for a new game
	void newGame();

	//Updates the game logic
	void update();

private:
	std::unique_ptr<AbstractGamePhase> state;

	void reset();

	//Updates the engine state to reflect the current phase
	void updatePhaseState();

	//Performs the game logic for the current phase
	void doPhase();

	//Progresses the game to the next phase
	void nextPhase();
};

