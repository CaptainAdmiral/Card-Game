#pragma once
#include "AbstractGamePhase.h"
#include <vector>

class Field;

typedef std::vector<std::pair<unsigned int, unsigned int>> CoordinatesVec;


class GamePhaseAction : public AbstractGamePhase {
public:
	GamePhaseAction(GameComponents&);
	~GamePhaseAction();
	void doPhase() override;


private:
	void doSummons(std::vector<Action::Summon> &summons) const;
	void doAttacks(std::vector<Action::Attack> &attacks) const;
	void doContestedBattles(std::vector<Action::Move> &moves) const;
	void doMoves(std::vector<Action::Move> &moves) const;

	ActionList mergeActions(ActionList &actions1, ActionList &actions2) const;
};