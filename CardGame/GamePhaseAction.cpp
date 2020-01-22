#include "GamePhaseAction.h"
#include "Actions.h"

GamePhaseAction::GamePhaseAction(GameComponents &components) : AbstractGamePhase(GamePhase::ACTION, components) {}

GamePhaseAction::~GamePhaseAction() {}

void GamePhaseAction::doPhase() {
	//Field playerField = getPredictedField(gameComponents.player.plannedActions);
	//Field player2Field = getPredictedField(gameComponents.player2.plannedActions);

	//gameComponents.field = mergeFields(playerField, player2Field);

	setFinished();
}

Field GamePhaseAction::getPredictedField(ActionList actions) {
	for(Action &action : actions) {
		switch(action.type) {
		case Action::MOVE:
			doMove(action.getMove());
			break;
			
		case Action::SUMMON:
			doSummon(action.getSummon());
			break;

		case Action::ATTACK:
			doAttack(action.getAttack());
				break;
		}
	}
	Field field;
	return field;
}

Field GamePhaseAction::mergeFields(const Field &field1, const Field &field2) {
	return Field();
}

void GamePhaseAction::doMove(Action::Move action) {
	Actions::move(action.card, action.slotTo);
}

void GamePhaseAction::doSummon(Action::Summon action) {}

void GamePhaseAction::doAttack(Action::Attack action) {}
