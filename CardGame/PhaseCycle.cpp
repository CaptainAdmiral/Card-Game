#include "PhaseCycle.h"

PhaseCycle::PhaseCycle() {}

PhaseCycle::~PhaseCycle() {}

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
	currentPhase = phaseVec.erase(std::find_if(phaseVec.begin(), phaseVec.end(), [&](Phase_t const &phase1) {
		return phase1.get() == phase;
	}));
}

void PhaseCycle::removePhase(Phase_t &phase) {
	removePhase(phase.get());
}

