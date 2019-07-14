#pragma once
#include "EnumGamePhase.h"

class AbstractGamePhase {
public:
	const GamePhase name;

	virtual ~AbstractGamePhase() {};

	virtual void doPhase() = 0;

protected:
	AbstractGamePhase(GamePhase phase) : name(phase) {}
};

