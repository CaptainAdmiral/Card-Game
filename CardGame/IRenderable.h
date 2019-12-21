#pragma once
#include "AbstractRender.h"
#include "BoundingBox.h"

class RenderManager;

class IRenderable {
public:
	int posX = 0;
	int posY = 0;
	BoundingBox boundingBox;

	IRenderable();
	virtual ~IRenderable();

	//Returning false will cause the render manager to skip the render pass for this object if it is on the render list
	virtual bool isVisible() {
		return true;
	}

	//Returns a reference to the render file to be used during the render pass
	virtual AbstractRender& getRender() = 0;

	//Mouse click and mouse release within TODO seconds
	virtual void onClicked() {};

	//On mouse click
	virtual void onMouseClick() {};
	
	//On mouse release
	virtual void onMouseRelease() {};
};