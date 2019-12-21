#pragma once
#include "IRenderable.h"
#include "RenderField.h"
#include "Slot.h"

class Field : IRenderable {
public:
	Field();
	~Field();

	std::unique_ptr<Slot> slotArray[6][5];

	AbstractRender &getRender() override;

	//TODO accept character array as seed for building field
	//e.g. {"#####", "######", "#P#P#", ""} std::make_pair('#',SlotTypes.DEFAULT), std::make_pair('P',SlotTypes.POWER_UP)
	//(The empty string is a possible differentiator between having a middle row and having no middle row)
	void buildField();

	//Creates and returns an array of all the cards on the field
	//Card **getCardsOnField();

	//bool isSlotEmpty(Slot&);

	//Return success
	//bool moveCard(Card&, Slot&);

	//Return success
	//bool moveCard(Slot&, Slot&);
};

