#pragma once
#include "AbstractRender.h"

class RenderManager;

class IRenderable {
public:
	int posX = 0;
	int posY = 0;
	//polygon shape;

	IRenderable();
	virtual ~IRenderable();

	virtual AbstractRender &getRender() = 0;

	virtual bool isVisible() {
		return true;
	}

	//Mouse click and mouse release within TODO seconds
	virtual void onClicked() {};

	//On mouse click
	virtual void onMouseClick() {};
	
	//On mouse release
	virtual void onMouseRelease() {};
};