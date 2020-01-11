#include "RulesManager.h"
#include "GameComponents.h"
#include "ValidateSummonEvent.h"
#include "ValidateMoveEvent.h"
#include "EventHandler.h"
#include "PhaseCycle.h"
#include "AbstractGamePhase.h"
#include "StandardGamePhases.h"

RulesManager::RulesManager(GameComponents &components, PhaseCycle &cycle) : gameComponents(components), phaseCycle(cycle) {
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
	LST.payload = [&](Event &e) {
		ValidateSummonEvent& summonEvent = static_cast<ValidateSummonEvent&>(e);
		if(summonEvent.validatePositionOnly) return;
		if(static_cast<std::vector<Card*>*>(phaseCycle.sharedInfo["summons"])->size() != 0) summonEvent.invalidate();
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
	LMCT.payload = [&](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		if(moveEvent.validatePositionOnly) return;
		Card* card = &moveEvent.card;
		if((*static_cast<std::map<Card*, int>*>(phaseCycle.sharedInfo["cardMoves"]))[&moveEvent.card]>0) moveEvent.invalidate();
	};
	LMCT.priority = Priority::BASE;
	rules.push_back(LMCT);

	//Stop movement on turn of summon
	Rule SMTS(ValidateMoveEvent::TYPE);
	SMTS.payload = [&](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		if(moveEvent.validatePositionOnly) return;
		std::vector<Card*> &vec = *static_cast<std::vector<Card*>*>(phaseCycle.sharedInfo["summons"]);
		if(std::find(vec.begin(), vec.end(), &moveEvent.card) != vec.end()) moveEvent.invalidate();
	};
	SMTS.priority = Priority::BASE;
	rules.push_back(SMTS);
}
