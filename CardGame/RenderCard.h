#pragma once
#include "AbstractRender.h"

class RenderCard : public AbstractRender {
public:
	RenderCard();
	~RenderCard();

	virtual void render(IRenderable &) override;
};

