#pragma once
#include "AbstractRender.h"

class RenderSlot : public AbstractRender {
public:
	RenderSlot();
	~RenderSlot();

	virtual void render(IRenderable &slot, RenderWrapper &wrapper) override;
};