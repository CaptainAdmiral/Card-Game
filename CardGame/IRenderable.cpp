#include "IRenderable.h"
#include "RenderManager.h"

IRenderable::IRenderable() {
	RenderManager::instance().addToRenderList(this);
}

IRenderable::~IRenderable() {
	RenderManager::instance().removeFromRenderList(this);
}
