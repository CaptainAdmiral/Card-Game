#include "Actions.h"
#include "Card.h"
#include "Slot.h"
#include "EventHandler.h"
#include "MoveEvent.h"

void Actions::move(Card &card, Slot &slot) {
	MoveEvent e(card, &slot);
	EventHandler::postEvent(e);
	if(e.isCanceled()) return;
	if(!e.slot->isEmpty()) {
		//TODO POLICY for card moved into occupied slot by effect
	}

	assert(e.card.container->giveCardTo(*e.slot));
	//Post card moved event
}

void Actions::summon(Card &card, Slot &slot) {
	assert(card.container->giveCardTo(slot));
}

void Actions::attack(Card &card, Slot &slot) {

}
