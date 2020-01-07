#include "RenderSlot.h"
#include "Slot.h"

RenderSlot::RenderSlot() {}

RenderSlot::~RenderSlot() {}

void RenderSlot::render(IRenderable &slot, RenderWrapper &rw) {
	using namespace Camera;
	const BoundingBox &BB = slot.getBoundingBox();
	sf::ConvexShape convex;
	convex.setPointCount(4);
	
	int i = 0;
	bg::for_each_point(BB, [&, i](point_t point) mutable {
		convex.setPoint(i, sf::Vector2f(SCREEN_X(point.get<0>()), SCREEN_Y(point.get<1>())));
		i++;
	});
	
	convex.setFillColor(sf::Color(150, 50, 250));
	rw.draw(convex);
}