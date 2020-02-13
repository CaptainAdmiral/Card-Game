#include "GamePhaseAction.h"
#include "Actions.h"
#include <vector>
#include <map>
#include <algorithm>


GamePhaseAction::GamePhaseAction(GameComponents &components) : AbstractGamePhase(GamePhase::ACTION, components) {

}

GamePhaseAction::~GamePhaseAction() {}

void GamePhaseAction::doPhase() {
	Field p1Field;
	Field p2Field;

	ActionList actions = mergeActions(gameComponents.player.plannedActions, gameComponents.player2.plannedActions);

	std::vector<Action::Summon> quickSummons;
	std::vector<Action::Attack> quickAttacks;
	std::vector<Action::Move> quickMoves;

	for(Action action : actions) {
		if(action.type == Action::SUMMON && action.speed == Action::FAST) {
			quickSummons.push_back(action.getSummon());
		}
	}

	for(Action action : actions) {
		if(action.type == Action::ATTACK && action.speed == Action::FAST) {
			quickAttacks.push_back(action.getAttack());
		}
	}

	for(Action action : actions) {
		if(action.type == Action::MOVE && action.speed == Action::FAST) {
			quickMoves.push_back(action.getMove());
		}
	}

	std::vector<Action::Summon> summons;
	std::vector<Action::Attack> attacks;
	std::vector<Action::Move> moves;

	doSummons(summons);
	doAttacks(attacks);
	doContestedBattles(moves);
	doMoves(moves);

	for(Action action : actions) {
		if(action.type == Action::SUMMON && action.speed == Action::SLOW) {
			summons.push_back(action.getSummon());
		}
	}

	for(Action action : actions) {
		if(action.type == Action::ATTACK && action.speed == Action::SLOW) {
			attacks.push_back(action.getAttack());
		}
	}

	for(Action action : actions) {
		if(action.type == Action::MOVE && action.speed == Action::SLOW) {
			moves.push_back(action.getMove());
		}
	}

	doSummons(summons);
	doAttacks(attacks);
	doContestedBattles(moves);
	doMoves(moves);

	setFinished();
}


void GamePhaseAction::doSummons(std::vector<Action::Summon>& summons) const {
	for(Action::Summon summon : summons) {
		gameComponents.field.slotArray[summon.to.first][summon.to.second]->card_in(std::make_unique<Card>(summon.card));
	}
}

void GamePhaseAction::doAttacks(std::vector<Action::Attack> &attacks) const {
	for(Action::Attack attack : attacks) {
		Card* attacker = gameComponents.field.slotArray[attack.attacker.first][attack.attacker.second]->contents.get();
		Card* attacked = gameComponents.field.slotArray[attack.attacked.first][attack.attacked.second]->contents.get();

		if(attacker && attacked && (attacker->owner != attacked->owner || !attacker->owner && !attacked->owner)) {
			Actions::attack(*attacker, *attacked);
		}
	}

	gameComponents.field.for_each_card([](Card &card) {
		if(card.properties.hp <= 0) {
			card.container->card_out();
		}
	});

	//TODO move card death on health 0 to rules, move can't attack if same owner to rules.
}

void GamePhaseAction::doContestedBattles(std::vector<Action::Move> &moves) const {
	for(Action::Move move : moves) {
		Card *card = gameComponents.field.slotArray[move.from.first][move.from.second]->contents.get();
		Slot *slot = gameComponents.field.slotArray[move.to.first][move.to.second].get();
		if(card == nullptr || !slot->isEmpty()) continue;
		for(Action::Move move2 : moves) {
			if(move.from == move2.from) continue;
			if(move.to == move2.to) {
				Card* attacker = gameComponents.field.slotArray[move.from.first][move.from.second]->contents.get();
				Card* attacked = gameComponents.field.slotArray[move2.from.first][move2.from.second]->contents.get();

				if(attacker && attacked && (attacker->owner != attacked->owner || !attacker->owner && !attacked->owner)) {
					Actions::attack(*attacker, *attacked);
				}
			}
		}
	}

	gameComponents.field.for_each_card([](Card &card) {
		if(card.properties.hp <= 0) {
			card.container->card_out();
		}
	});

	//TODO move card death on health 0 to rules, move can't attack if same owner to rules.
}
void GamePhaseAction::doMoves(std::vector<Action::Move>& moves) const {
	for(Action::Move move : moves) {
		Card *card = gameComponents.field.slotArray[move.from.first][move.from.second]->contents.get();
		Slot *slot = gameComponents.field.slotArray[move.to.first][move.to.second].get();
		if(card == nullptr || !slot->isEmpty()) continue;
		bool canMove = true;
		for(Action::Move move2 : moves) {
			if(move.from == move2.from) continue;
			if(move.to == move2.to) {
				Card* attacker = gameComponents.field.slotArray[move.from.first][move.from.second]->contents.get();
				Card* attacked = gameComponents.field.slotArray[move2.from.first][move2.from.second]->contents.get();

				if(!attacker || attacked) {
					canMove = false; //TODO move to rules
					break;
				}
			}
		}
		//post valid move event and check
		if(canMove) Actions::move(*card, *slot);
	}
}

ActionList GamePhaseAction::mergeActions(ActionList &actions1, ActionList &actions2) const {
	ActionList actionList;
	size_t i1 = actions1.size();
	size_t i2 = actions2.size();

	while(i1 != 0 || i2 != 0) {
		unsigned int r = rand() % (i1 + i2);

		if(r < i1) {
			actionList.push_back(actions1.at(--i1));
		}
		else {
			actionList.push_back(actions2.at(--i2));
		}
	}

	return actionList;
}
