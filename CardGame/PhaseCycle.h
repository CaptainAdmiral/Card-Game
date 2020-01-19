#pragma once
#include <vector>
#include <map>
#include <memory>

class AbstractGamePhase;

typedef std::unique_ptr<AbstractGamePhase> Phase_t;
typedef std::vector<Phase_t> PhaseVec;

class PhaseCycle {
public:
	PhaseCycle();
	~PhaseCycle();

	unsigned int turnNumber = 0;

	void addPhaseAtStart(Phase_t&);
	void addPhaseAtEnd(Phase_t&);
	void addPhaseAfter(Phase_t&);
	void addPhaseBefore(Phase_t&);

	void removePhase(AbstractGamePhase*);
	void removePhase(Phase_t&);

	Phase_t &getCurrentPhase();
	void setCurrentPhase(Phase_t&);

	void nextPhase();

private:
	//Iterator representing the current phase in the turn cycle
	PhaseVec::iterator currentPhase;

	friend class GameStateManager;
	PhaseVec phaseVec;
};

