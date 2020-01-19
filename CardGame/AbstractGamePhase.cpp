#pragma once
#include "AbstractGamePhase.h"

AbstractGamePhase::AbstractGamePhase(GamePhase phase, GameComponents &components, Player *player, PhaseCycle *turnCycle) : name(phase), gameComponents(components), player(player), turnCycle(turnCycle) {}
AbstractGamePhase::~AbstractGamePhase() {}

void AbstractGamePhase::update() {
	//Eventbus.PostEvent(new phaseEvent(*this, EventStage::PRE))
	doPhase();
	//Eventbus.PostEvent(new phaseEvent(*this, EventStage::POST))
}

void AbstractGamePhase::setFinished() {
	finished = true;
}

bool AbstractGamePhase::isFinished() {
	return finished;
}