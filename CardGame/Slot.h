#pragma once
#include "ICardContainer.h"


class Slot : public ICardContainer, public IRenderable {
public:
	Slot();
	Slot(float x, float y);
	Slot(float x, float y, float width, float height);
	~Slot();

	CardPtr contents;

	//Assert slot is empty (use isEmpty() or hasSpace() to check)
	virtual void card_in(CardPtr) override;
	virtual CardPtr card_out() override;
	virtual CardPtr card_out(Card&) override;
	virtual bool hasSpace() override;
	virtual bool isEmpty() override;
	virtual bool contains(Card&) override;

	virtual AbstractRender& getRender() override;

	virtual RenderType getType() override;

	float getHeight() {
		return height;
	}

	float getWidth() {
		return width;
	}

	void setWidth(float w) {
		width = w;
		updateBoundingBox();
	}

	void setHeight(float h) {
		height = h;
		updateBoundingBox();
	}

protected:
	float height = 0;
	float width = 0;

	virtual BoundingBox calculateBoundingBox() override;
};