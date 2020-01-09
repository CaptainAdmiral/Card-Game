#pragma once
#include "IRenderable.h"
#include "Slot.h"

class Field : IRenderable {
public:
	Field();
	Field(const Field&);
	Field &operator=(const Field&);
	~Field();

	std::unique_ptr<Slot> slotArray[5][5];

	AbstractRender &getRender() override;

	//TODO accept character array as seed for building field
	//e.g. {"#####", "######", "#P#P#", ""} std::make_pair('#',SlotTypes.DEFAULT), std::make_pair('P',SlotTypes.POWER_UP)
	//(The empty string is a possible differentiator between having a middle row and having no middle row)
	void buildField();

	void buildField(const Field&);
};

