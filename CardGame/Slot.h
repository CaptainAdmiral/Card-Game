#pragma once
#include "ICardContainer.h"
#include "RenderSlot.h"

class Slot : ICardContainer, public IRenderable {
public:
	Slot();
	Slot(float x, float y);
	Slot(float x, float y, float size);
	~Slot();

	CardPtr contents;

	float size = 0;

	//Assert slot is empty (use isEmpty() or hasSpace() to check)
	virtual void card_in(CardPtr) override;
	virtual CardPtr card_out() override;
	virtual CardPtr card_out(Card&) override;
	virtual bool hasSpace() override;
	virtual bool isEmpty() override;
	virtual bool contains(Card&) override;

	virtual AbstractRender& getRender() override;
	virtual BoundingBox calculateBoundingBox() override;
};