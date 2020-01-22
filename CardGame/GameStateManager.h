#pragma once
#include <memory>

struct GameComponents;
class PhaseCycle;


class GameStateManager {
public:
	GameComponents &gameComponents;
	PhaseCycle &cycle;

	GameStateManager(GameComponents& components, PhaseCycle &cycle);
	~GameStateManager();

	//Updates the game logic
	void update();

private:
	//Performs the game logic for the current phase
	void updatePhase();
};

