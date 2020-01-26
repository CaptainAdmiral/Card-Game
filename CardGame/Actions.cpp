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

	assert(e.card.container->giveCardTo(*e.slot, e.card));
	//Post card moved event
}

void Actions::summon(Card &card, Slot &slot) {
	assert(card.container->giveCardTo(slot, card));
}

void Actions::attackSlot(Slot &slot, std::vector<Card*> attackers) {
	if(!slot.contents) return;
	Card& attacked = *slot.contents;

	int buffer = 0;

	if(attacked.isCountering) {
		buffer = attacked.properties.ctr; //TODO
	}

	for(auto&& attacker : attackers) {
		buffer -= attacker->properties.atk;
	}

	if(buffer > 0) {
		for(auto&& attacker : attackers) {
			attack(attacked, *attacker);
		}
	}
}

void Actions::attack(Card &attacker, Card &attacked) {
	attacked.properties.setHp(attacked.properties.hp - attacked.properties.atk);
}
