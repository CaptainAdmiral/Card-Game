#pragma once
#include "IRenderable.h"
#include "Slot.h"

class Field : IRenderable {
public:
	Field();
	Field(const Field&);
	Field &operator=(const Field&);
	~Field();

	std::unique_ptr<Slot> slotArray[10][9];

	AbstractRender &getRender() override;

	//TODO accept character array as seed for building field
	//e.g. {"#####", "######", "#P#P#", ""} std::make_pair('#',SlotTypes.DEFAULT), std::make_pair('P',SlotTypes.POWER_UP)
	//(The empty string is a possible differentiator between having a middle row and having no middle row)
	void buildField();

	//Deep copies the contents of the supplied field
	void buildField(const Field&);

	//Causes the fields slots not to be rendered and the cards to be rendered semi-transparently
	void displayAsAfterimage(bool flag);

	//Brings all the cards on the field to the front of the render list;
	void bringCardsToFront();

	//Executes the function on each card on the field;
	void for_each_card(void(*func)(Card&));
};

