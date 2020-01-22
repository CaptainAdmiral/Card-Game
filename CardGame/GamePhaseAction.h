#pragma once
#include "AbstractGamePhase.h"
#include <vector>

class Field;

class GamePhaseAction : public AbstractGamePhase {
public:
	GamePhaseAction(GameComponents&);
	~GamePhaseAction();
	void doPhase() override;

private:
	//iterates the actions list on a copy of the current field to produce a field with predictive positioning.
	//reenacts the planning phase with events that might not be known to the player.
	Field getPredictedField(ActionList actions);

	//Merges the given fields. Cards occupying the same slot battle, and remain where they were unless one of them is destroyed.
	//If a card's final location deviates from it's predicted location 
	Field mergeFields(const Field& field1, const Field& field2);

	void doMove(Action::Move action);
	void doSummon(Action::Summon action);
	void doAttack(Action::Attack action);
};