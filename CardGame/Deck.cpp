#include "Deck.h"

Deck::Deck(Player &owner) : owner(owner) {}
Deck::~Deck() {}

//TODO
void Deck::card_in(CardPtr) {}

CardPtr Deck::card_out() {
	CardPtr card = std::make_unique<Card>(owner);
	card.get()->properties.setAtk(10).setCtr(12).setHp(8).setSpeed(1).setRange(1);
	return std::move(card);
}

CardPtr Deck::card_out(Card &) {
	return nullptr;
}

bool Deck::hasSpace() {
	return true;
}

bool Deck::contains(Card &) {
	return false;
}

bool Deck::isEmpty() {
	return false;
}
