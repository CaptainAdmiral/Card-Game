#pragma once
#include "AbstractGamePhase.h"
#include <vector>

class Field;

typedef std::vector<std::pair<unsigned int, unsigned int>> ConflictsVec;


class GamePhaseAction : public AbstractGamePhase {
public:
	GamePhaseAction(GameComponents&);
	~GamePhaseAction();
	void doPhase() override;

private:
	//iterates the actions list on a copy of the current field to produce a field with predictive positioning.
	//reenacts the planning phase with events that might not be known to the player.
	Field getPredictedField(ActionList actions, Player &player);

	ActionList getResolvedConflicts(const ActionList &actions, ConflictsVec conflicts);

	void doBattles(Field &field1, Field &field2);


	Slot &getSlotForField(Slot& slot, Field &field);
	Card &getCardForField(Card& card, Field &field);
};