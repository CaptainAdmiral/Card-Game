#include "Slot.h"

Slot::Slot() {
}

Slot::~Slot() {
}

void Slot::card_in(CardPtr card) {
	assert(isEmpty());
	contents=std::move(card);
	card->slot = this;
}

CardPtr Slot::card_out() {
	assert(!isEmpty());
	contents->slot = nullptr;
	return std::move(contents);
}

CardPtr Slot::card_out(Card& card) {
	assert(contains(card));
	return Slot::card_out();
}

bool Slot::hasSpace() {
	return isEmpty();
}

bool Slot::isEmpty() {
	return !contents;
}

bool Slot::contains(Card& card) {
	return contents.get() == &card;
}

AbstractRender &Slot::getRender() {
	static RenderSlot render;
	return render;
}
