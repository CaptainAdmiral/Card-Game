#pragma once
#include "RenderWrapper.h"
#include <string>

class IRenderable;

class AbstractRender {
public:
	AbstractRender();
	virtual ~AbstractRender();

	virtual void render(IRenderable &renderable, RenderWrapper) = 0;
};

