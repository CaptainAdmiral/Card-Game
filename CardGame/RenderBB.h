#pragma once
#include "AbstractRender.h"

class RenderBB : public AbstractRender {
public:
	RenderBB();
	RenderBB(sf::Color color);
	~RenderBB();

	void render(IRenderable &renderable, RenderWrapper &rw) override;

	sf::Color color = sf::Color(150, 50, 250);
};

