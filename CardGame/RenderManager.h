#pragma once
#include "RenderWrapper.h"
#include "IRenderable.h"
#include <vector>

class RenderManager {
public:
	~RenderManager();

	//Sets the current RenderWindow to draw to
	void setWindow(sf::RenderWindow &window) {
		wrapper = std::make_unique<RenderWrapper>(RenderWrapper{window});
	}

	//RenderManager singleton instance
	static RenderManager &instance();

	//Adds an IRenderable to the list of objects to be rendered
	//Recommended Usage - RenderManager::instance().addToRenderList(this); in IRenderable constructor
	void addToRenderList(IRenderable *);

	//Removes an IRenderable from the list of objects to be rendered
	//Recommended Usage - RenderManager::instance().removeFromRenderList(this); in IRenderable destructor
	void removeFromRenderList(IRenderable *);

	//Perform the render pass
	void doRender();

	//Mouse hitscan for last clickable renderable in the render list
	//The thing on screen being clicked
	//Return pointer to IRenderable or nullptr if nothing was hit
	IRenderable *getClicked(int x, int y);
	
private:
	std::unique_ptr<RenderWrapper> wrapper;

	RenderManager();
	RenderManager(const RenderManager&) = delete;
	RenderManager(RenderManager&&) = delete;
	RenderManager &operator = (const RenderManager&) = delete;
	RenderManager &operator = (RenderManager&&) = delete;

	std::vector<IRenderable*> renderList;
};