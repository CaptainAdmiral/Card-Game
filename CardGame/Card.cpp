#include "Card.h"


Card::Card() {
	
}
Card::Card(Card::Properties props) {
	Card();
	properties = props;
}

Card::~Card() {
	
}

AbstractRender &Card::getRender() {
	static RenderCard render;
	return render;
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