#pragma once
#include "EnumGamePhase.h"
#include "GameComponents.h"

class PhaseCycle;

class AbstractGamePhase {
public:
	const GamePhase name;
	GameComponents &gameComponents;
	PhaseCycle *const turnCycle;
	Player *const player;

	virtual ~AbstractGamePhase();

	//Called when the current phase switches over to this phase
	virtual void onPhaseStart() {}

	//Called on the currently phase before the current phase changes
	//Does not necessarily mean the phase has finished
	virtual void onPhaseEnd() {}

	//Update the phase, called every tick
	virtual void update();

	//Calling will cause the turn cycle to move onto the next phase after the current phase update, or skip the phase next time it is due if it is not the current phase
	void setFinished();

	bool isFinished();

protected:
	AbstractGamePhase(GamePhase phase, GameComponents&, Player* player = nullptr, PhaseCycle* phaseCycle = nullptr);

private:
	friend class GameStateManager;
	bool finished = false;

	virtual void doPhase() = 0;
};