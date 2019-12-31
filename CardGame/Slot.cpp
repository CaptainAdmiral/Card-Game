#include "Slot.h"

Slot::Slot() {
	updateBoundingBox();
}

Slot::Slot(float x, float y) {
	setPos(x, y);
}

Slot::Slot(float x, float y, float size) : size(size) {
	setPos(x, y);
}

Slot::~Slot() {}

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

BoundingBox Slot::calculateBoundingBox() {
	BoundingBox BB;
	bg::append(BB.outer(), point_t(posX - size/2, posY));
	bg::append(BB.outer(), point_t(posX, posY + size));
	bg::append(BB.outer(), point_t(posX + size/2, posY));
	bg::append(BB.outer(), point_t(posX, posY - size));

	return BB;
}
