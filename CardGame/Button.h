#pragma once
#include "IRenderable.h"

class Button : public IRenderable {
public:
	unsigned int height;
	unsigned int width;

	Button();
	Button(unsigned int h, unsigned int w);
	~Button();
};

