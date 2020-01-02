#include "Hand.h"

Hand::Hand() {
	updateBoundingBox();
}
Hand::Hand(float x, float y) {
	setPos(x, y);
}

Hand::~Hand() {
	updateBoundingBox();
}

void Hand::card_in(CardPtr card) {
	card->setPos(posX, posY);
	AbstractCardContainer::card_in(std::move(card));
}

AbstractRender &Hand::getRender() {
	static DummyRender render;
	static RenderBB debugRender(sf::Color::Green);
	if(!Settings::Debug::DEBUG) {
		return render;
	}
	else {
		return debugRender;
	}
}

BoundingBox Hand::calculateBoundingBox() {
	unsigned int width = Settings::General::DEFAULT_WIDTH;
	float height = Settings::UI::handHeight;

	BoundingBox BB;
	bg::append(BB.outer(), point_t(posX-width/2, posY-height/2));
	bg::append(BB.outer(), point_t(posX+width/2, posY-height/2));
	bg::append(BB.outer(), point_t(posX+width/2, posY+height/2));
	bg::append(BB.outer(), point_t(posX-width/2, posY+height/2));

	return BB;
}
