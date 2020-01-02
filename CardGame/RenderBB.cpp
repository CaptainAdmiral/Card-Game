#include "RenderBB.h"
#include "IRenderable.h"

RenderBB::RenderBB() {}

RenderBB::RenderBB(sf::Color color) : color(color) {}

RenderBB::~RenderBB() {}

void RenderBB::render(IRenderable &renderable, RenderWrapper &rw) {
	using namespace Camera;
	const BoundingBox &BB = renderable.getBoundingBox();
	sf::ConvexShape convex;
	convex.setPointCount(BB.outer().size());

	int i = 0;
	bg::for_each_point(BB, [&, i](point_t point) mutable {
		convex.setPoint(i, sf::Vector2f(SCREEN_X(point.get<0>()), SCREEN_Y(point.get<1>())));
		i++;
	});

	convex.setFillColor(color);
	rw.draw(convex);
}