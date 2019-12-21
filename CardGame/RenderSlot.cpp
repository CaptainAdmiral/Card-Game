#include "RenderSlot.h"

RenderSlot::RenderSlot() {}


RenderSlot::~RenderSlot() {}

void RenderSlot::render(IRenderable &renderable, RenderWrapper) {
	static_cast<Slot&>(renderable);
}
