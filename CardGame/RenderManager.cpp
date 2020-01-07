#include "RenderManager.h"
#include "AbstractRender.h"

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