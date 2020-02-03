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
	//TODO Post card moved event
}

void Actions::summon(Card &card, Slot &slot) {
	assert(card.container->giveCardTo(slot, card));
}

void Actions::attack(Card &attacked, std::vector<Card*> attackers) {
	if(attacked.isCountering) {
		attacked.buffer = attacked.properties.ctr; //TODO move to action phase
	}

	for(Card *attacker : attackers) {
		attack(*attacker, attacked);
	}

	if(attacked.buffer > 0) {
		for(Card *attacker : attackers) {
			counterAttack(attacked, *attacker);
		}
	}
}

void Actions::attack(Card &attacker, Card &attacked) {
	attacked.properties.setHp(attacked.properties.hp - attacked.properties.atk);
}

void Actions::counterAttack(Card &counterAttacker, Card &counterAttacked) {
	counterAttacked.properties.setHp(counterAttacked.properties.hp - counterAttacker.buffer);
}