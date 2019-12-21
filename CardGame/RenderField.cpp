#include "RenderField.h"
#include <iostream>

RenderField::RenderField() {}

RenderField::~RenderField() {}

void RenderField::render(IRenderable &renderable, RenderWrapper rw) {
	sf::CircleShape shape(250.f);
	shape.setFillColor(sf::Color(100, 250, 50));
	
	rw.draw(shape);
}