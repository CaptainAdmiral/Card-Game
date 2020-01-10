#pragma once
#include "RenderWrapper.h"
#include "Camera.h"

class IRenderable;

class AbstractRender {
public:
	AbstractRender() {}
	virtual ~AbstractRender() {}

	virtual void render(IRenderable &renderable, RenderWrapper &wrapper) = 0;
};
