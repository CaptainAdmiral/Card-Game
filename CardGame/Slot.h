#pragma once
#include "ICardContainer.h"

class Slot : public ICardContainer, public IRenderable {
public:
	static constexpr GameObjectType TYPE = GameObjectType::SLOT;

	int row = 0;
	int col = 0;

	Slot();
	Slot(float x, float y);
	Slot(float x, float y, float width, float height);
	Slot(float x, float y, float width, float height, int row, int col);
	virtual ~Slot();

	CardPtr contents;

	//Assert slot is empty (use isEmpty() or hasSpace() to check)
	virtual void card_in(CardPtr) override;
	virtual CardPtr card_out() override;
	virtual CardPtr card_out(Card&) override;
	virtual bool hasSpace() override;
	virtual bool isEmpty() override;
	virtual bool contains(Card&) override;

	virtual AbstractRender& getRender() override;

	virtual GameObjectType getType() override;

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

	virtual GameObjectType type() override {
		return TYPE;
	}

protected:
	float height = 0;
	float width = 0;

	virtual BoundingBox calculateBoundingBox() override;
};