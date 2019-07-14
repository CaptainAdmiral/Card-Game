#include "Card.h"


Card::Card() {}
Card::Card(Card::Properties props) {
	properties = props;
}

Card::~Card() {}

Card::Properties &Card::Properties::setAtk(int i) {
	atk = i;
	return *this;
}

Card::Properties &Card::Properties::setDef(int i) {
	def = i;
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