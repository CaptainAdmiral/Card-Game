#pragma once
#include "AbstractRender.h"
#include "Slot.h"

class RenderSlot : public AbstractRender {
public:
	RenderSlot();
	~RenderSlot();

	virtual void render(IRenderable &slot, RenderWrapper &wrapper) override;
};