#pragma once
#include "AbstractCardContainer.h"
#include "IRenderable.h"

class Hand : public AbstractCardContainer, public IRenderable {
public:
	Hand();
	Hand(float x, float y);
	~Hand();

	virtual void card_in(CardPtr) override;
	virtual CardPtr card_out() override;
	virtual CardPtr card_out(Card &card) override;

	virtual AbstractRender& getRender() override;
	virtual BoundingBox calculateBoundingBox() override;
private:
	//Calculates and updates the x y position of all cards in the hand
	void updateCardPositions();
};