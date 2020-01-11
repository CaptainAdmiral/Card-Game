#include "RulesManager.h"
#include "GameComponents.h"
#include "ValidateSummonEvent.h"
#include "ValidateMoveEvent.h"
#include "EventHandler.h"

RulesManager::RulesManager(GameComponents &components) : gameComponents(components) {
	EventHandler::subscribe(this);
	addBaseRules();
}
RulesManager::~RulesManager() {}

void RulesManager::notify(Event &e) {
	for(Rule rule : rules) {
		if(rule.trigger == e.getType()) {
			if(rule.meetsRequirements(e)) {
				rule.activate(e);
			}
		}
	}
}

void RulesManager::addBaseRules() {
	//First row summon
	Rule FRS(ValidateSummonEvent::TYPE);
	FRS.payload = [](Event &e) {
		ValidateSummonEvent& summonEvent = static_cast<ValidateSummonEvent&>(e);
		if(summonEvent.slot.row != 0) summonEvent.invalidate();
	};
	rules.push_back(FRS);

	//Limit summons per turn
	Rule LST(ValidateSummonEvent::TYPE);
	LST.payload = [](Event &e) {
		ValidateSummonEvent& summonEvent = static_cast<ValidateSummonEvent&>(e);
		if(summonEvent.prevSummons != 0) summonEvent.invalidate();
	};
	rules.push_back(LST);

	//Limit move distance
	Rule LMD(ValidateMoveEvent::TYPE);
	LMD.payload = [](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		Slot &slotFrom = *static_cast<Slot*>(moveEvent.card.container);
		Slot &slotTo = moveEvent.slot;
		if(abs(slotTo.row-slotFrom.row)!=1 || (slotTo.col != slotFrom.col && slotTo.col != slotFrom.col-2*(slotFrom.row%2)+1)) moveEvent.invalidate();
	};
	rules.push_back(LMD);

	//Limit moves card per turn
	Rule LMCT(ValidateMoveEvent::TYPE);
	LMCT.payload = [](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		if(moveEvent.prevMoves!=0) moveEvent.invalidate();
	};
	rules.push_back(LMCT);
}
