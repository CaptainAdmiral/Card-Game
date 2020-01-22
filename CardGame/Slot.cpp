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

Slot::Slot(float x, float y, float width, float height, int row, int col) : width(width), height(height), row(row), col(col) {
	setPos(x, y);
}

Slot::~Slot() {}

GameObjectType Slot::getType() {
	return GameObjectType::SLOT;
}

void Slot::card_in(CardPtr card) {
	assert(isEmpty());
	card->container = this;
	card->isInSlot = true;
	contents=std::move(card);
}

CardPtr Slot::card_out() {
	assert(!isEmpty());
	contents->container = nullptr;
	contents->isInSlot = false;
	CardPtr temp = std::move(contents);
	contents = nullptr;
	return std::move(temp);
}

CardPtr Slot::card_out(Card& card) {
	assert(contains(card));
	return Slot::card_out();
}

bool Slot::hasSpace() {
	return isEmpty();
}

bool Slot::isEmpty() {
	return contents == nullptr;
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
	//bg::append(BB.outer(), point_t(posX - width/2, posY));
	//bg::append(BB.outer(), point_t(posX, posY + height/2));
	//bg::append(BB.outer(), point_t(posX + width/2, posY));
	//bg::append(BB.outer(), point_t(posX, posY - height/2));
	//bg::append(BB.outer(), point_t(posX - width / 2, posY));

	bg::append(BB.outer(), point_t(posX + width / 4, posY - height / 2));
	bg::append(BB.outer(), point_t(posX + width / 2, posY));
	bg::append(BB.outer(), point_t(posX + width / 4, posY + height / 2));
	bg::append(BB.outer(), point_t(posX - width / 4, posY + height / 2));
	bg::append(BB.outer(), point_t(posX - width / 2, posY));
	bg::append(BB.outer(), point_t(posX - width / 4, posY - height / 2));
	bg::append(BB.outer(), point_t(posX + width / 4, posY - height / 2));

	return BB;
}
