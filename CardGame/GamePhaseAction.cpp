#include "GamePhaseAction.h"
#include "Actions.h"
#include <vector>
#include <map>
#include <time.h>
#include <algorithm>

//TODO when resolving conflicts for unit with multiple moves resolve conflicts with earlier moves first to determine if later moves still happen

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
		field.for_each_slot([](Slot &slot) {
			slot.properties.visitors.clear();
			slot.properties.attackers.clear();
		});

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
		else if(slot.contents) {
			slot.properties.visitors.push_back(slot.contents.get());
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
			if(std::find(conflicts.begin(), conflicts.end(), move.to) != conflicts.end()) {
				newActions.push_back(Action::Move(move.to, move.from));
			}
		}
	}

	return newActions;
}

void GamePhaseAction::doBattles(Field &field1, Field &field2) {
	//std::vector<CardPtr> deadCards;

	//for(size_t i = 0; i < std::size(gameComponents.field.slotArray); i++) {
	//	for(size_t j = 0; j < std::size(gameComponents.field.slotArray[i]); j++) {
	//		if(Field::slotMissing(i, j)) continue;
	//		std::vector<Card*> attackers;
	//		std::vector<Card*> visitors;

	//		//Combine info for slot attack and visitor vectors between prodicted fields
	//		std::vector<Card*> &f1AtkVec = field1.slotArray[i][j]->properties.attackers;
	//		std::vector<Card*> &f2AtkVec = field2.slotArray[i][j]->properties.attackers;
	//		attackers.insert(attackers.end(), f1AtkVec.begin(), f1AtkVec.end());
	//		attackers.insert(attackers.end(), f2AtkVec.begin(), f2AtkVec.end());

	//		std::vector<Card*> &f1VisVec = field1.slotArray[i][j]->properties.visitors;
	//		std::vector<Card*> &f2VisVec = field2.slotArray[i][j]->properties.visitors;
	//		visitors.insert(visitors.end(), f1VisVec.begin(), f1VisVec.end());
	//		visitors.insert(visitors.end(), f2VisVec.begin(), f2VisVec.end());

	//		attackers.insert(attackers.end(), visitors.begin(), visitors.end());

	//		attackers.erase(std::unique(attackers.begin(), attackers.end()), attackers.end());
	//		visitors.erase(std::unique(visitors.begin(), visitors.end()), visitors.end());

	//		for(Card *card : visitors) {
	//			std::vector<Card*> enemyAttackers = attackers;
	//			enemyAttackers.erase(std::remove_if(enemyAttackers.begin(), enemyAttackers.end(), [&](Card *card1) {return card->owner == card1->owner;}), enemyAttackers.end());
	//			Actions::attack(*card, enemyAttackers);
	//			if(card->properties.hp < 0) {
	//				if(card->container != nullptr) deadCards.push_back(card->container->card_out());
	//			}
	//		}
	//	}

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

			Actions::move(*card, *slot);
			break;

		case Action::SUMMON:
			//doSummon(action.getSummon()); //TODO summon from hand copy
			getSlotForField(action.getSummon().slot, field).card_in(std::make_unique<Card>(action.getSummon().card));
			break;

		case Action::ATTACK:
			action.getAttack().target.properties.attackers.push_back(&action.getAttack().card);
			break;
		}
	}
}

Slot &GamePhaseAction::getSlotForField(Slot& slot, Field &field) {
	return *field.slotArray[slot.row][slot.col];
}

Card &GamePhaseAction::getCardForField(Card& card, Field &field) {
	return *field.slotArray[static_cast<Slot*>(card.container)->row][static_cast<Slot*>(card.container)->col]->contents; //TODO 
}
