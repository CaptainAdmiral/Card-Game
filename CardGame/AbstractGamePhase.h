#pragma once
#include "EnumGamePhase.h"
#include "GameComponents.h"

class PhaseCycle;

class AbstractGamePhase {
public:
	const GamePhase name;
	GameComponents &gameComponents;
	PhaseCycle *turnCycle;

	virtual ~AbstractGamePhase();

	virtual void update();

	void setFinished();

	bool isFinished();

protected:
	AbstractGamePhase(GamePhase phase, GameComponents&);
	AbstractGamePhase(GamePhase phase, GameComponents&, PhaseCycle*);

private:
	friend class GameStateManager;
	bool finished = false;

	virtual void doPhase() = 0;
};