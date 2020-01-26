#include "GamePhaseAction.h"
#include "Actions.h"
#include <vector>
#include <map>
#include <time.h>
#include <algorithm>

GamePhaseAction::GamePhaseAction(GameComponents &components) : AbstractGamePhase(GamePhase::ACTION, components) {}

GamePhaseAction::~GamePhaseAction() {}

void GamePhaseAction::doPhase() {
	setFinished();
	return;
	const Field &field = gameComponents.field;
	Field p1Field;
	Field p2Field;

	ActionList p1PlannedActions = gameComponents.player.plannedActions;
	ActionList p2PlannedActions = gameComponents.player2.plannedActions;

	ConflictsVec conflicts;

	//In the event order is deterministic of final state order is determined randomly,
	//although with good design order will hopefully never be deterministic of final state.
	srand(time(NULL));
	bool player1First = rand()%2;

	do  {
		conflicts.clear();

		p1Field = getPredictedField(p1PlannedActions, gameComponents.player);
		p2Field = getPredictedField(p2PlannedActions, gameComponents.player2);

		doBattles(p1Field, p2Field);

		for(size_t i = 0; i < std::size(field.slotArray); i++) {
			for(size_t j = 0; j < std::size(field.slotArray[i]); j++) {
				if(Field::slotMissing(i, j)) continue;
				if(p1Field.slotArray[i][j]->contents && p1Field.slotArray[i][j]->contents) {
					conflicts.push_back(std::make_pair(i, j));
				}
			}
		}

		if(player1First) {
			p1PlannedActions = getResolvedConflicts(p1PlannedActions, conflicts);
			p2PlannedActions = getResolvedConflicts(p2PlannedActions, conflicts);
		}
		else {
			p2PlannedActions = getResolvedConflicts(p2PlannedActions, conflicts);
			p1PlannedActions = getResolvedConflicts(p1PlannedActions, conflicts);
		}
	}
	while(!conflicts.empty());

	setFinished();
}

Field GamePhaseAction::getPredictedField(ActionList actions, Player &player) {
	Field field = gameComponents.field;

	for(Action &action : actions) {
		switch(action.type) {
		case Action::MOVE:
			Actions::move(getCardForField(action.getMove().card, field), getSlotForField(action.getMove().slotTo, field));
			break;
			
		case Action::SUMMON:
			//doSummon(action.getSummon()); //TODO summon from hand copy
			break;

		case Action::ATTACK:
			action.getAttack().target.properties.attackers.push_back(&action.getAttack().card);
			break;
		}
	}
	field.for_each_slot([&](Slot& slot) {
		if(slot.contents && slot.contents->owner != &player) {
			slot.card_out();
		}
	});

	return field;
}

//Resolution policies must ensure state change moves towards known state of zero conflict
ActionList GamePhaseAction::getResolvedConflicts(const ActionList &actions, ConflictsVec conflicts) {
	ActionList newActions;

	//Edit the actions to add move back to good boy tile if accidentally move into no-no tile
	for(Action action : actions) {
		newActions.push_back(action);
		if(action.type == Action::MOVE) {
			Action::Move move = action.getMove();
			if(std::find(conflicts.begin(), conflicts.end(), std::make_pair((unsigned int)move.slotTo.row, (unsigned int)move.slotTo.col)) != conflicts.end()) {
				newActions.push_back(Action::Move(move.card, static_cast<Slot&>(*move.card.container)));
			}
		}
	}

	return newActions;
}

void GamePhaseAction::doBattles(Field &field1, Field &field2) {
	for(size_t i = 0; i < std::size(gameComponents.field.slotArray); i++) {
		for(size_t j = 0; j < std::size(gameComponents.field.slotArray[i]); j++) {
			if(Field::slotMissing(i, j)) continue;
			std::vector<Card*> attackers;

			//Share info for slot attack and visitor vectors between prodicted fields
			std::vector<Card*> &f1AtkVec = field1.slotArray[i][j]->properties.attackers;
			std::vector<Card*> &f2AtkVec = field2.slotArray[i][j]->properties.attackers;
			attackers.insert(attackers.end(), f1AtkVec.begin(), f1AtkVec.end());
			attackers.insert(attackers.end(), f2AtkVec.begin(), f2AtkVec.end());

			std::vector<Card*> &f1VisVec = field1.slotArray[i][j]->properties.visitors;
			std::vector<Card*> &f2VisVec = field2.slotArray[i][j]->properties.visitors;
			attackers.insert(attackers.end(), f1VisVec.begin(), f1VisVec.end());
			attackers.insert(attackers.end(), f2VisVec.begin(), f2VisVec.end());

			attackers.erase(std::unique(attackers.begin(), attackers.end()), attackers.end());

			Actions::attackSlot(*field1.slotArray[i][j], attackers);
			Actions::attackSlot(*field2.slotArray[i][j], attackers);
		}
	}
}

Slot &GamePhaseAction::getSlotForField(Slot& slot, Field &field) {
	return *field.slotArray[slot.row][slot.col];
}

Card &GamePhaseAction::getCardForField(Card& card, Field &field) {
	return *field.slotArray[static_cast<Slot*>(card.container)->row][static_cast<Slot*>(card.container)->col]->contents;
}
