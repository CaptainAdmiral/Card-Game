#pragma once
#include <string>

class IRenderable;

class AbstractRender {
public:
	AbstractRender();
	virtual ~AbstractRender();

	virtual void render(IRenderable&) = 0;
};

