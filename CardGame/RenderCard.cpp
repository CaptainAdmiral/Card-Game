#include "RenderCard.h"
#include "Card.h"


RenderCard::RenderCard() {}
RenderCard::~RenderCard() {}

void RenderCard::render(IRenderable &renderable, RenderWrapper rw) {
	Card &card = static_cast<Card&>(renderable);
}