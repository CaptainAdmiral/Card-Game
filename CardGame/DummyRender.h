#pragma once
#include "AbstractRender.h"

class DummyRender : public AbstractRender {
public:
	DummyRender() {}
	~DummyRender() {}

	inline virtual void render(IRenderable &renderable, RenderWrapper &rw) override {}
};