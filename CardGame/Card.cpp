#include "Card.h"
#include "RenderCard.h"
#include "Slot.h"


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
	BoundingBox BB;
	
	if(!isInSlot) {
		float height = Settings::UI::handHeight*0.8f;
		float width = Settings::UI::cardWidth;

		bg::append(BB.outer(), point_t(posX - width / 2, posY - height / 2));
		bg::append(BB.outer(), point_t(posX + width / 2, posY - height / 2));
		bg::append(BB.outer(), point_t(posX + width / 2, posY + height / 2));
		bg::append(BB.outer(), point_t(posX - width / 2, posY + height / 2));
		bg::append(BB.outer(), point_t(posX - width / 2, posY - height / 2));

		return BB;
	}

	Slot &slot = *static_cast<Slot*>(container);
	
	//namespace trans = boost::geometry::strategy::transform;

	//BoundingBox bb;

	//trans::translate_transformer<double, 2, 2> translateToZero(-posX, -posY);
	//trans::translate_transformer<double, 2, 2> translateBack(posX, posY);
	//trans::scale_transformer<double, 2, 2> scale(0.8);

	//boost::geometry::transform(slot.getBoundingBox(), BB, translateToZero);
	//boost::geometry::transform(BB, bb, scale);
	//boost::geometry::transform(bb, BB, translateBack);

	//return BB;

	bg::append(BB.outer(), point_t(posX - slot.getWidth() / 2.4, posY));
	bg::append(BB.outer(), point_t(posX, posY + slot.getHeight() / 2.4));
	bg::append(BB.outer(), point_t(posX + slot.getWidth() / 2.4, posY));
	bg::append(BB.outer(), point_t(posX, posY - slot.getHeight() / 2.4));
	bg::append(BB.outer(), point_t(posX - slot.getWidth() / 2.4, posY));

	return BB;
}

GameObjectType Card::getType() {
	return GameObjectType::CARD;
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