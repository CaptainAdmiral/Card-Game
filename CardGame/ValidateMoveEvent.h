#pragma once
#include "Event.h"
#include "IValidationEvent.h"

class Card;
class Slot;

class ValidateMoveEvent : public Event, public IValidationEvent {
public:
	static const unsigned int TYPE;
	Card &card;
	Slot &slot;

	ValidateMoveEvent(Card &card, Slot &slot) : card(card), slot(slot) {}
	~ValidateMoveEvent() {}

	virtual const unsigned int getType() {
		return TYPE;
	}
};

