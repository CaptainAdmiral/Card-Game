#pragma once
#pragma once
#include "Event.h"

class Card;
class Slot;

class MoveEvent : public Event {
public:
	static constexpr EventType TYPE = "Move";
	Card &card;
	Slot *slot;

	MoveEvent(Card &card, Slot *slot) : card(card), slot(slot) {}
	virtual ~MoveEvent() {}

	virtual EventType getType() {
		return TYPE;
	}

	virtual bool isCancelable() {
		return true;
	}
};

