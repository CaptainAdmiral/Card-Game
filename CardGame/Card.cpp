#include "Card.h"
#include <iostream>

Card::Card() {
	updateBoundingBox();
}
Card::Card(Card::Properties props) {
	Card();
	properties = props;
	updateBoundingBox();
}

Card::~Card() {
	
}

AbstractRender &Card::getRender() {
	static RenderBB render(sf::Color::Red);
	return render;
}

BoundingBox Card::calculateBoundingBox() {
	float height = Settings::UI::handHeight;
	float width = height/2;

	BoundingBox BB;
	bg::append(BB.outer(), point_t(posX - width / 2, posY - height / 2));
	bg::append(BB.outer(), point_t(posX + width / 2, posY - height / 2));
	bg::append(BB.outer(), point_t(posX + width / 2, posY + height / 2));
	bg::append(BB.outer(), point_t(posX - width / 2, posY + height / 2));

	return BB;
}

Card::Properties &Card::Properties::setAtk(int i) {
	atk = i;
	return *this;
}

Card::Properties &Card::Properties::setDef(int i) {
	def = i;
	return *this;
}

Card::Properties &Card::Properties::setCtr(int i) {
	ctr = i;
	return *this;
}

Card::Properties &Card::Properties::setSpeed(int i) {
	speed = i;
	return *this;
}

Card::Properties &Card::Properties::setRange(int i) {
	range = i;
	return *this;
}