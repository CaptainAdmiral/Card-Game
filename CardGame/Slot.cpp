#include "Slot.h"
#include "RenderBB.h"

Slot::Slot() {
	updateBoundingBox();
}

Slot::Slot(float x, float y) {
	setPos(x, y);
}

Slot::Slot(float x, float y, float width, float height) : width(width), height(height) {
	setPos(x, y);
}

Slot::~Slot() {}

RenderType Slot::getType() {
	return RenderType::SLOT;
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
	static RenderBB render;
	return render;
}

BoundingBox Slot::calculateBoundingBox() {
	BoundingBox BB;
	bg::append(BB.outer(), point_t(posX - width/2, posY));
	bg::append(BB.outer(), point_t(posX, posY + height/2));
	bg::append(BB.outer(), point_t(posX + width/2, posY));
	bg::append(BB.outer(), point_t(posX, posY - height/2));
	bg::append(BB.outer(), point_t(posX - width / 2, posY));

	return BB;
}
