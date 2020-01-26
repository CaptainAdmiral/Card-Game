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

	//Summon on summon tile
	Rule SOST(ValidateSummonEvent::TYPE);
	SOST.payload = [](Event &e) {
		ValidateSummonEvent& summonEvent = static_cast<ValidateSummonEvent&>(e);
		if(summonEvent.slot.properties.type != Slot::Properties::SUMMON) { summonEvent.invalidate(); return; }
		if(summonEvent.card.owner && summonEvent.card.owner != summonEvent.slot.properties.getController()) summonEvent.invalidate();
	};
	SOST.priority = Priority::BASE;
	rules.push_back(SOST);

	//Limit summons per turn
	Rule LST(ValidateSummonEvent::TYPE);
	LST.payload = [&](Event &e) {
		ValidateSummonEvent& summonEvent = static_cast<ValidateSummonEvent&>(e);
		if(summonEvent.validatePositionOnly) return;
		if(summonEvent.card.owner == nullptr) return;
		if(summonEvent.card.owner->summons > 0) summonEvent.invalidate(); //TODO swap out for buff
	};
	LST.priority = Priority::BASE;
	rules.push_back(LST);

	//Limit move distance
	Rule LMD(ValidateMoveEvent::TYPE);
	LMD.payload = [](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		Slot &slotFrom = *static_cast<Slot*>(moveEvent.card.container);
		Slot &slotTo = moveEvent.slot;
		if(slotTo.col - slotFrom.col == 0) {
			if(abs(slotTo.row - slotFrom.row) > 1) moveEvent.invalidate();
		}
		else if(abs(slotTo.col - slotFrom.col) == 1) {
			if(slotTo.row != slotFrom.row && slotTo.row != slotFrom.row - 2*(slotFrom.col % 2) + 1) moveEvent.invalidate();
		}
		else {
			moveEvent.invalidate();
		}
	};
	LMD.priority = Priority::BASE;
	rules.push_back(LMD);

	//No move on void tile
	Rule NMOV(ValidateMoveEvent::TYPE);
	NMOV.payload = [](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		if(moveEvent.slot.properties.type == Slot::Properties::VOID) moveEvent.invalidate();
	};
	NMOV.priority = Priority::BASE;
	rules.push_back(NMOV);

	//Limit moves per card per turn
	Rule LMCT(ValidateMoveEvent::TYPE);
	LMCT.payload = [&](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		if(moveEvent.validatePositionOnly) return;
		if(moveEvent.card.moves>0) moveEvent.invalidate(); //TODO swap out for buff
	};
	LMCT.priority = Priority::BASE;
	rules.push_back(LMCT);

	//Stop movement on turn of summon
	Rule SMTS(ValidateMoveEvent::TYPE);
	SMTS.payload = [&](Event &e) {
		ValidateMoveEvent& moveEvent = static_cast<ValidateMoveEvent&>(e);
		if(moveEvent.validatePositionOnly) return;
		if(moveEvent.card.justSummoned) moveEvent.invalidate(); //TODO swap out for buff
	};
	SMTS.priority = Priority::BASE;
	rules.push_back(SMTS);
}
