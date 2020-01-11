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
		assert(rule.priority != Priority::INVALID);
		if(rule.trigger == e.getType()) {
			if(rule.meetsRequirements(e)) {
				rule.activate(e);
			}
		}
	}
}

void RulesManager::addBaseRules() {
	//Slot is empty on summon
	Rule SIES(ValidateSummonEvent::TYPE);
	SIES.payload = [](Event &e) {
		ValidateSummonEvent& summonEvent = static_cast<ValidateSummonEvent&>(e);
		if(!summonEvent.slot.isEmpty()) summonEvent.invalidate();
	};
	SIES.priority = Priority::BASE;
	rules.push_back(SIES);

	//Slot is empty on move
	Rule SIEM(ValidateMoveEvent::TYPE);
	SIEM.payload = [](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		if(!moveEvent.slot.isEmpty()) moveEvent.invalidate();
	};
	SIEM.priority = Priority::BASE;
	rules.push_back(SIEM);

	//First row summon
	Rule FRS(ValidateSummonEvent::TYPE);
	FRS.payload = [](Event &e) {
		ValidateSummonEvent& summonEvent = static_cast<ValidateSummonEvent&>(e);
		if(summonEvent.slot.row != 0) summonEvent.invalidate();
	};
	FRS.priority = Priority::BASE;
	rules.push_back(FRS);

	//Limit summons per turn
	Rule LST(ValidateSummonEvent::TYPE);
	LST.payload = [](Event &e) {
		ValidateSummonEvent& summonEvent = static_cast<ValidateSummonEvent&>(e);
		if(summonEvent.prevSummons != 0) summonEvent.invalidate();
	};
	LST.priority = Priority::BASE;
	rules.push_back(LST);

	//Limit move distance
	Rule LMD(ValidateMoveEvent::TYPE);
	LMD.payload = [](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		Slot &slotFrom = *static_cast<Slot*>(moveEvent.card.container);
		Slot &slotTo = moveEvent.slot;
		if(abs(slotTo.row-slotFrom.row)!=1 || (slotTo.col != slotFrom.col && slotTo.col != slotFrom.col-2*(slotFrom.row%2)+1)) moveEvent.invalidate();
	};
	LMD.priority = Priority::BASE;
	rules.push_back(LMD);

	//Limit moves per card per turn
	Rule LMCT(ValidateMoveEvent::TYPE);
	LMCT.payload = [](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		if(moveEvent.prevMoves!=0) moveEvent.invalidate();
	};
	LMCT.priority = Priority::BASE;
	rules.push_back(LMCT);
}
