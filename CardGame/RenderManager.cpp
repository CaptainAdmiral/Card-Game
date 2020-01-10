#include "RenderManager.h"
#include "AbstractRender.h"
#include "IRenderable.h"


RenderManager::RenderManager() {}

RenderManager::~RenderManager() {}

RenderManager &RenderManager::instance() {
	static RenderManager instance;
	return instance;
}

void RenderManager::addToRenderList(IRenderable *renderable) {
	renderList.push_back(renderable);
}

void RenderManager::removeFromRenderList(IRenderable *renderable) {
	renderList.erase(std::find(renderList.begin(), renderList.end(), renderable));
	
}

void RenderManager::doRender() {
	for(auto &&renderable : renderList) {
		if(renderable->isVisible()) {
			renderable->getRender().render(*renderable, *wrapper);
		}
	}
}

void RenderManager::bringToFront(IRenderable *renderable) {
	removeFromRenderList(renderable);
	addToRenderList(renderable);
}

IRenderable *RenderManager::getHit(int x, int y) {
	for(auto it = renderList.rbegin(); it != renderList.rend(); it++) {
		IRenderable *renderable = *it;
		if(renderable->isClickable() && boost::geometry::within(point_t(x, y), renderable->getBoundingBox())) return renderable;
	}
	return nullptr;
}

IRenderable * RenderManager::getHitWithIgnore(int x, int y, IRenderable *ignore) {
	for(auto it = renderList.rbegin(); it != renderList.rend(); it++) {
		IRenderable *renderable = *it;
		if(renderable != ignore && renderable->isClickable() && boost::geometry::within(point_t(x, y), renderable->getBoundingBox())) return renderable;
	}
	return nullptr;
}
