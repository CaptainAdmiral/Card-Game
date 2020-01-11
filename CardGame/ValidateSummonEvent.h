#pragma once
#include "Event.h"
#include "IValidationEvent.h"

class Card;
class Slot;

class ValidateSummonEvent : public Event, public IValidationEvent {
public:
	static constexpr EventType TYPE = "Validate_Summon";
	Card &card;
	Slot &slot;
	int prevSummons;

	ValidateSummonEvent(Card &card, Slot &slot, int summons) : card(card), slot(slot), prevSummons(summons) {}
	~ValidateSummonEvent() {}

	virtual EventType getType() {
		return TYPE;
	}
};

