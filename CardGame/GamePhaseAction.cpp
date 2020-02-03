#include "GamePhaseAction.h"
#include "Actions.h"
#include <vector>
#include <map>
#include <time.h>
#include <algorithm>


GamePhaseAction::GamePhaseAction(GameComponents &components) : AbstractGamePhase(GamePhase::ACTION, components) {}

GamePhaseAction::~GamePhaseAction() {}

void GamePhaseAction::doPhase() {
	Field &field = gameComponents.field;
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

		doBattles(p1Field, p2Field); //TODO do battle after each move rather than at end (remember to do battles once before moves)

		for(size_t i = 0; i < std::size(field.slotArray); i++) {
			for(size_t j = 0; j < std::size(field.slotArray[i]); j++) {
				if(Field::slotMissing(i, j)) continue;
				if(p1Field.slotArray[i][j]->contents && p2Field.slotArray[i][j]->contents) {
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

	gameComponents.field.for_each_slot([](Slot& slot) {
		if(!slot.isEmpty()) slot.card_out();
	});

	for(size_t i = 0; i < std::size(gameComponents.field.slotArray); i++) {
		for(size_t j = 0; j < std::size(gameComponents.field.slotArray[i]); j++) {
			if(Field::slotMissing(i, j)) continue;
			if(p1Field.slotArray[i][j]->contents) gameComponents.field.slotArray[i][j]->card_in(std::move(p1Field.slotArray[i][j]->contents));
			if(p2Field.slotArray[i][j]->contents) gameComponents.field.slotArray[i][j]->card_in(std::move(p2Field.slotArray[i][j]->contents));

		}
	}

	setFinished();
}

Field GamePhaseAction::getPredictedField(ActionList actions, Player &player) {
	Field field = gameComponents.field;

	applyActionsToField(actions, field);

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
		if(action.type == Action::MOVE) {
			Action::Move move = action.getMove();
			if(std::find(conflicts.begin(), conflicts.end(), move.to) != conflicts.end()) {
				continue;
			}
		}
		newActions.push_back(action);
	}

	return newActions;
}

void GamePhaseAction::doBattles(Field &field1, Field &field2) {
	for(size_t i = 0; i < std::size(gameComponents.field.slotArray); i++) {
		for(size_t j = 0; j < std::size(gameComponents.field.slotArray[i]); j++) {
			if(Field::slotMissing(i, j)) continue;
			if(field1.slotArray[i][j]->contents && field2.slotArray[i][j]->contents) {
				Actions::attack(*field1.slotArray[i][j]->contents, *field2.slotArray[i][j]->contents);
				Actions::attack(*field2.slotArray[i][j]->contents, *field1.slotArray[i][j]->contents);
				if(field1.slotArray[i][j]->contents->properties.hp < 0) {
					field1.slotArray[i][j]->card_out();
				}
				if(field2.slotArray[i][j]->contents->properties.hp < 0) {
					field2.slotArray[i][j]->card_out();
				}
			}
		}
	}
}

void GamePhaseAction::applyActionsToField(ActionList &actions, Field &field) {
	Card *card;
	Slot *slot;

	for(Action &action : actions) {
		switch(action.type) {
		case Action::MOVE:
			card = field.slotArray[action.getMove().from.first][action.getMove().from.second]->contents.get();
			slot = field.slotArray[action.getMove().to.first][action.getMove().to.second].get();
			if(card == nullptr) continue;

			//post valid move event and check

			Actions::move(*card, *slot);
			break;

		case Action::SUMMON:
			field.slotArray[action.getSummon().to.first][action.getSummon().to.second]->card_in(std::make_unique<Card>(action.getSummon().card));
			break;

		case Action::ATTACK:
			
			break;
		}
	}
}
