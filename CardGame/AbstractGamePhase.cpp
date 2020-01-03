#pragma once
#include "AbstractGamePhase.h"

AbstractGamePhase::AbstractGamePhase(GamePhase phase, GameComponents &components) : name(phase), gameComponents(components) {}
AbstractGamePhase::AbstractGamePhase(GamePhase phase, GameComponents &components, std::vector<std::unique_ptr<AbstractGamePhase>> *turnCycle) : name(phase), gameComponents(components), turnCycle(turnCycle)  {}
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