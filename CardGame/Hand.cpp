#include "Hand.h"
#include "DummyRender.h"
#include "RenderBB.h"
#include "Settings.h"


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
	AbstractCardContainer::card_in(std::move(card));
	updateCardPositions();
}

CardPtr Hand::card_out() {
	updateCardPositions();
	return AbstractCardContainer::card_out();
}

CardPtr Hand::card_out(Card &card) {
	updateCardPositions();
	return AbstractCardContainer::card_out(card);
}

void Hand::updateCardPositions() {
	size_t size = contents.size();
	float width = Settings::UI::cardWidth;
	if(Settings::General::DEFAULT_WIDTH >= width*size) {
		for(size_t i=0; i != size; i++) {
			contents[i]->setPos(posX-width*(size - 1)/2 + i*width, posY);
		}
	}
	else {
		for(size_t i=0; i != size; i++) {
			contents[i]->setPos(width/2 + i*(Settings::General::DEFAULT_WIDTH - width) / (size - 1), posY);
		}
	}
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
	bg::append(BB.outer(), point_t(posX-width/2, posY-height/2));

	return BB;
}
