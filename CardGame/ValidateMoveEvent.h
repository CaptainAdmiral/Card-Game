#pragma once
#include "Event.h"
#include "IValidationEvent.h"

class Card;
class Slot;

class ValidateMoveEvent : public Event, public IValidationEvent {
public:
	static constexpr EventType TYPE = "Validate_Move";
	Card &card;
	Slot &slot;
	bool validatePositionOnly = false;

	ValidateMoveEvent(Card &card, Slot &slot) : card(card), slot(slot) {}
	virtual ~ValidateMoveEvent() {}

	virtual EventType getType() {
		return TYPE;
	}
};

