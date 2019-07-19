#pragma once
#include "IRenderable.h"
#include <vector>

class RenderManager {
public:
	~RenderManager();

	static RenderManager &instance();

	void addToRenderList(IRenderable*);
	void removeFromRenderList(IRenderable*);

	void doRender();

private:
	RenderManager();
	RenderManager(const RenderManager&) = delete;
	RenderManager(RenderManager&&) = delete;
	RenderManager &operator = (const RenderManager&) = delete;
	RenderManager &operator = (RenderManager&&) = delete;

	std::vector<std::pair<IRenderable*, AbstractRender*>> renderList;
};

