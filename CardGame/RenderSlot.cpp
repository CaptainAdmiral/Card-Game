#include "RenderSlot.h"
#include "Slot.h"
#include "Player.h"
#include <algorithm> 

RenderSlot::RenderSlot() {}

RenderSlot::~RenderSlot() {}

void RenderSlot::render(IRenderable &renderable, RenderWrapper &rw) {
	Slot &slot = static_cast<Slot&>(renderable);

	using namespace Camera;
	const BoundingBox &BB = slot.getBoundingBox();
	sf::ConvexShape convex;
	convex.setPointCount(BB.outer().size());

	int i = 0;
	bg::for_each_point(BB, [&, i](point_t point) mutable {
		convex.setPoint(i, sf::Vector2f(SCREEN_X(point.get<0>()), SCREEN_Y(point.get<1>())));
		i++;
	});

	sf::Color playerColor(100, 100, 100);

	if(slot.properties.getController()) {
		playerColor = sf::Color(std::get<0>(slot.properties.getController()->getColor()), std::get<1>(slot.properties.getController()->getColor()), std::get<2>(slot.properties.getController()->getColor()));
	}

	switch(slot.properties.type) {
	case(Slot::Properties::VOID):
		convex.setFillColor(sf::Color(20, 20, 20));
		break;
	case(Slot::Properties::PLAINS):
		convex.setFillColor(sf::Color(255, 255, 255));
		break;
	case(Slot::Properties::SUMMON):
		convex.setFillColor(sf::Color(std::min(playerColor.r + 80, 255), std::min(playerColor.g + 80, 255), std::min(playerColor.b + 80, 255)));
		break;
	case(Slot::Properties::BASE):
		convex.setFillColor(playerColor);
		break;
	case(Slot::Properties::MANA):
		convex.setFillColor(sf::Color(100, 100, 255));
		break;
	default:
		convex.setFillColor(sf::Color(0, 0, 0));
		break;
	}
	rw.draw(convex);
}