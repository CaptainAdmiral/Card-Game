#pragma once
#include "EnumGamePhase.h"
#include "GameComponents.h"

class AbstractGamePhase {
public:
	const GamePhase name;
	GameComponents &gameComponents;
	std::vector<std::unique_ptr<AbstractGamePhase>> *turnCycle;

	virtual ~AbstractGamePhase();

	virtual void update();

	void setFinished();

	bool isFinished();

protected:
	AbstractGamePhase(GamePhase phase, GameComponents&);
	AbstractGamePhase(GamePhase phase, GameComponents&, std::vector<std::unique_ptr<AbstractGamePhase>>*);

private:
	bool finished = false;

	virtual void doPhase() = 0;
};

typedef std::vector<std::unique_ptr<AbstractGamePhase>> TurnCycle;