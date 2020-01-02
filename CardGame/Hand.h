#pragma once
#include "AbstractCardContainer.h"
#include "IRenderable.h"
#include "DummyRender.h"
#include "RenderBB.h"
#include "Settings.h"

class Hand : public AbstractCardContainer, public IRenderable {
public:
	Hand();
	Hand(float x, float y);
	~Hand();

	virtual void card_in(CardPtr) override;

	virtual AbstractRender& getRender() override;
	virtual BoundingBox calculateBoundingBox() override;
};