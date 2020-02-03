#include "Slot.h"
#include "RenderSlot.h"

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

float Slot::getHeight() {
	return height;
}

float Slot::getWidth() {
	return width;
}

void Slot::setWidth(float w) {
	width = w;
	updateBoundingBox();
}

void Slot::setHeight(float h) {
	height = h;
	updateBoundingBox();
}

void Slot::card_in(CardPtr card) {
	assert(isEmpty());
	card->container = this;
	card->isInSlot = true;
	contents=std::move(card);
	contents->setPos(posX, posY);
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
	static RenderSlot render;
	return render;
}

Player *Slot::Properties::getController() {
	return controller;
}

void Slot::Properties::setController(Player *player) {
	controller = player;
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
