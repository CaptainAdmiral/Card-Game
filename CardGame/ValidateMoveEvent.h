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
	int prevMoves;

	ValidateMoveEvent(Card &card, Slot &slot, int moves) : card(card), slot(slot), prevMoves(moves) {}
	~ValidateMoveEvent() {}

	virtual EventType getType() {
		return TYPE;
	}
};

