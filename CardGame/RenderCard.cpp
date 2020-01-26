#include "RenderCard.h"
#include "Card.h"


RenderCard::RenderCard() {}
RenderCard::~RenderCard() {}

void RenderCard::render(IRenderable &renderable, RenderWrapper &rw) {
	Card &card = static_cast<Card&>(renderable);
	using namespace Camera;
	const BoundingBox &BB = renderable.getBoundingBox();
	sf::ConvexShape convex;
	convex.setPointCount(BB.outer().size());

	int i = 0;
	bg::for_each_point(BB, [&, i](point_t point) mutable {
		convex.setPoint(i, sf::Vector2f(SCREEN_X(point.get<0>()), SCREEN_Y(point.get<1>())));
		i++;
	});

	sf::Color color;
	color = sf::Color::Black;
	color.a = card.isAfterimage ? 5 : 255;
	convex.setFillColor(color);
	rw.draw(convex);

	namespace trans = boost::geometry::strategy::transform;

	BoundingBox bb;
	BoundingBox bb1;

	float x = renderable.getPosX();
	float y = renderable.getPosY();

	trans::translate_transformer<double, 2, 2> translateToZero(-x, -y);
	trans::translate_transformer<double, 2, 2> translateBack(x, y);
	trans::scale_transformer<double, 2, 2> scale(0.9);
	
	boost::geometry::transform(BB, bb, translateToZero);
	boost::geometry::transform(bb, bb1, scale);
	boost::geometry::transform(bb1, bb, translateBack);

	i = 0;
	bg::for_each_point(bb, [&, i](point_t point) mutable {
		convex.setPoint(i, sf::Vector2f(SCREEN_X(point.get<0>()), SCREEN_Y(point.get<1>())));
		i++;
	});

	color = sf::Color::Magenta;
	color.a = card.isAfterimage ? 170 : 255;
	convex.setFillColor(color);
	rw.draw(convex);


	boost::geometry::transform(bb, bb1, translateToZero);
	boost::geometry::transform(bb1, bb, scale);
	boost::geometry::transform(bb, bb1, translateBack);

	i = 0;
	bg::for_each_point(bb1, [&, i](point_t point) mutable {
		convex.setPoint(i, sf::Vector2f(SCREEN_X(point.get<0>()), SCREEN_Y(point.get<1>())));
		i++;
	});

	color = sf::Color::White;
	color.a = card.isAfterimage ? 170 : 255;
	convex.setFillColor(color);
	rw.draw(convex);
}