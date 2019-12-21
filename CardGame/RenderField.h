#pragma once
#include "AbstractRender.h"
class Field;

class RenderField : public AbstractRender {
public:
	RenderField();
	~RenderField();

	virtual void render(IRenderable &renderable, RenderWrapper rw) override;
};

