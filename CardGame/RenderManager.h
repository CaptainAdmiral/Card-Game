#pragma once
#include "RenderWrapper.h"
#include <vector>

class IRenderable;

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
	void addToRenderList(IRenderable*);

	//Removes an IRenderable from the list of objects to be rendered
	//Recommended Usage - RenderManager::instance().removeFromRenderList(this); in IRenderable destructor
	void removeFromRenderList(IRenderable*);

	//Perform the render pass
	void doRender();

	//Sends the specified IRenderable to the back of the renderlist (front of screen)
	void bringToFront(IRenderable*);

	//Mouse hitscan for last clickable renderable in the render list
	//The thing on screen being clicked
	//Return pointer to IRenderable or nullptr if nothing was hit
	IRenderable *getHit(int x, int y);

	//Mouse hitscan for last clickable renderable in the render list
	//The thing on screen being clicked
	//Return pointer to IRenderable or nullptr if nothing was hit
	//Para ignore - IRenderable* parameter to be ignored during hitscan. Hitscan will continue through ignore if it is the first thing hit.
	IRenderable *getHitWithIgnore(int x, int y, IRenderable *ignore);
	
private:
	std::unique_ptr<RenderWrapper> wrapper;

	RenderManager();
	RenderManager(const RenderManager&) = delete;
	RenderManager(RenderManager&&) = delete;
	RenderManager &operator = (const RenderManager&) = delete;
	RenderManager &operator = (RenderManager&&) = delete;

	std::vector<IRenderable*> renderList; //TODO this should be a set or have duplicate checking on insertion
};