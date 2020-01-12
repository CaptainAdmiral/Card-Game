#include "PhaseCycle.h"
#include "AbstractGamePhase.h"

PhaseCycle::PhaseCycle() {}

PhaseCycle::~PhaseCycle() {}

void PhaseCycle::nextPhase() {
	(**currentPhase).onPhaseEnd();
	++currentPhase;
	if(currentPhase == phaseVec.end()) {
		turnNumber++;
		currentPhase = phaseVec.begin();
	}
	(**currentPhase).onPhaseStart();
}

void PhaseCycle::addPhaseAtStart(Phase_t &phase) {
	phaseVec.insert(phaseVec.begin(), std::move(phase));
}

void PhaseCycle::addPhaseAtEnd(Phase_t &phase) {
	phaseVec.push_back(std::move(phase));
}

void PhaseCycle::addPhaseAfter(Phase_t &phase) {
	phaseVec.insert(++std::find(phaseVec.begin(), phaseVec.end(), phase), std::move(phase));
}

void PhaseCycle::addPhaseBefore(Phase_t &phase) {
	phaseVec.insert(std::find(phaseVec.begin(), phaseVec.end(), phase), std::move(phase));
}

void PhaseCycle::removePhase(AbstractGamePhase *phase) {
	if(currentPhase->get() == phase) {
		phase->onPhaseEnd();
	}
	currentPhase = phaseVec.erase(std::find_if(phaseVec.begin(), phaseVec.end(), [&](Phase_t const &phase1) {
		return phase1.get() == phase;
	}));
}

void PhaseCycle::removePhase(Phase_t &phase) {
	removePhase(phase.get());
}

Phase_t &PhaseCycle::getCurrentPhase() {
	return *currentPhase;
}

void PhaseCycle::setCurrentPhase(Phase_t &phase) {
	if(*currentPhase != phase) {
		(*currentPhase)->onPhaseEnd();
	}
}
