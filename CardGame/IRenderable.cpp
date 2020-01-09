#include "IRenderable.h"
#include "RenderManager.h"

IRenderable::IRenderable() {
	RenderManager::instance().addToRenderList(this);
	updateBoundingBox();
}

IRenderable::IRenderable(const IRenderable &renderable) {
	posX = renderable.posX;
	posY = renderable.posY;
	RenderManager::instance().addToRenderList(this);
	updateBoundingBox();
}

IRenderable &IRenderable::operator=(const IRenderable &renderable) {
	posX = renderable.posX;
	posY = renderable.posY;
	RenderManager::instance().addToRenderList(this);
	updateBoundingBox();
	return *this;
}

IRenderable::~IRenderable() {
	RenderManager::instance().removeFromRenderList(this);
}

void IRenderable::setPos(float x, float y) {
	posX = x;
	posY = y;
	updateBoundingBox();
}

void IRenderable::move(float x, float y) {
	posX += x;
	posY += y;
	updateBoundingBox();
}
