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

	//hashmap for sharing information between phases
	//WARNING:
	//Phase's are responsible for adding and removing pointers from the shared info
	//in their implementation, there is no saftey checking to make sure data is removed
	//and delete is called when no longer needed.
	std::map<std::string, void*> sharedInfo;

	//Iterator representing the current phase in the turn cycle
	PhaseVec::iterator currentPhase;

	unsigned int turnNumber = 0;

	void addPhaseAtStart(Phase_t&);
	void addPhaseAtEnd(Phase_t&);
	void addPhaseAfter(Phase_t&);
	void addPhaseBefore(Phase_t&);

	void removePhase(AbstractGamePhase*);
	void removePhase(Phase_t&);

private:
	friend class GameStateManager;
	PhaseVec phaseVec;
};

