#pragma once
#include "EnumGamePhase.h"
#include "GameComponents.h"

class AbstractGamePhase {
public:
	GameComponents &gameComponents;
	const GamePhase name;

	virtual ~AbstractGamePhase();

	virtual void update();

	void setFinished();

	bool isFinished();

protected:
	AbstractGamePhase(GamePhase phase, GameComponents&);

private:
	bool finished = false;

	virtual void doPhase() = 0;
};

