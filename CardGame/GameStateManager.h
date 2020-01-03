#pragma once
#include "StandardGamePhases.h"
#include <memory>

class GameStateManager {
public:
	GameComponents &gameComponents;

	GameStateManager(GameComponents& components);
	~GameStateManager();

	//Resets the game engine for a new game
	void newGame();

	//Updates the game logic
	void update();

	//void addPhase(AbstractGamePhase &phase, AbstractGamePhase &after)

private:
	TurnCycle::iterator currentPhase;

	TurnCycle turnCycle;
	
	void reset();

	//Progresses the game to the next phase
	void nextPhase();

	//Performs the game logic for the current phase
	void updatePhase();
};

