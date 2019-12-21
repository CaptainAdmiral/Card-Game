#pragma once
#include "AbstractRender.h"
class Card;

class RenderCard : public AbstractRender {
public:
	RenderCard();
	~RenderCard();

	virtual void render(IRenderable &renderable, RenderWrapper rw) override;
};

