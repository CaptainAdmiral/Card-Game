#pragma once
#include "Slot.h"

class Field {
public:
	Field();
	~Field();

	Slot **slotArray;

	//TODO accept character array as seed for building field
	//e.g. {"#####", "######", "#P#P#", ""} std::make_pair('#',SlotTypes.DEFAULT), std::make_pair('P',SlotTypes.POWER_UP)
	//(The empty string is a possible differentiator between having a middle row and having no middle row)
	void buildField();

	//Creates and returns an array of all the cards on the field
	Card **getCardsOnField();

	bool isSlotEmpty(Slot&);

	//Return success
	bool moveCard(Card&, Slot&);

	//Return success
	bool moveCard(Slot&, Slot&);
};

