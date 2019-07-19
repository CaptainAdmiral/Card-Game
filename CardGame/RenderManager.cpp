#include "RenderManager.h"


RenderManager::RenderManager() {}


RenderManager::~RenderManager() {}

RenderManager &RenderManager::instance() {
	static RenderManager instance;
	return instance;
}

void RenderManager::addToRenderList(IRenderable *renderable) {
	renderList.push_back(std::make_pair(renderable, &renderable->getRender()));
}

void RenderManager::removeFromRenderList(IRenderable *renderable) {
	std::vector<std::pair<IRenderable*, AbstractRender*>>::iterator iterator = std::find(renderList.begin(), renderList.end(), std::make_pair(renderable, &renderable->getRender()));
	renderList.erase(iterator);
	
}

void RenderManager::doRender() {
	for(auto &&pair : renderList) {
		IRenderable &renderable = *pair.first;
		AbstractRender &renderer = *pair.second;
		renderer.render(renderable);
	}
}
