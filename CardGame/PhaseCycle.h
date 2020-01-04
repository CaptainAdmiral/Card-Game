#pragma once
#include "AbstractGamePhase.h"
#include <vector>
#include <memory>

typedef std::unique_ptr<AbstractGamePhase> Phase_t;
typedef std::vector<Phase_t> PhaseVec;

class PhaseCycle {
public:
	PhaseCycle();
	~PhaseCycle();

	void addPhaseAtStart(Phase_t&);
	void addPhaseAtEnd(Phase_t&);
	void addPhaseAfter(Phase_t&);
	void addPhaseBefore(Phase_t&);

	void removePhase(AbstractGamePhase*);
	void removePhase(Phase_t&);

private:
	friend class GameStateManager;
	PhaseVec phaseVec;
	PhaseVec::iterator currentPhase;
};

