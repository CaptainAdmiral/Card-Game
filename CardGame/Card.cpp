#include "Card.h"
#include "RenderCard.h"


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
	static RenderCard render;
	return render;
}

BoundingBox Card::calculateBoundingBox() {
	float height = Settings::UI::handHeight*0.8f;
	float width = Settings::UI::cardWidth;

	BoundingBox BB;
	bg::append(BB.outer(), point_t(posX - width / 2, posY - height / 2));
	bg::append(BB.outer(), point_t(posX + width / 2, posY - height / 2));
	bg::append(BB.outer(), point_t(posX + width / 2, posY + height / 2));
	bg::append(BB.outer(), point_t(posX - width / 2, posY + height / 2));
	bg::append(BB.outer(), point_t(posX - width / 2, posY - height / 2));

	return BB;
}

RenderType Card::getType() {
	return RenderType::CARD;
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