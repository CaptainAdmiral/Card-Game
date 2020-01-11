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
	bool validatePositionOnly = false;

	ValidateSummonEvent(Card &card, Slot &slot) : card(card), slot(slot) {}
	virtual ~ValidateSummonEvent() {}

	virtual EventType getType() {
		return TYPE;
	}
};

