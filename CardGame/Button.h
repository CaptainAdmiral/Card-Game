#pragma once
#include "IRenderable.h"
#include "RenderBB.h"

template<typename Functor, typename Instance = void>
class Button : public IRenderable {
public:
	unsigned int height;
	unsigned int width;
	Instance* instance;
	Functor func;

	Button() {}
	Button(int x, int y, unsigned int h, unsigned int w) : posX(x), posY(y), height(h), width(w) {}
	Button(int x, int y, unsigned int h, unsigned int w, Functor func) : posX(x), posY(y), height(h), width(w), func(func) {}
	virtual ~Button() {}

	virtual void onMouseClick() override {
		(instance->*func)();
	}

	virtual AbstractRender& getRender() override {
		static RenderBB render{sf::Color(100, 100, 100)};
		return render;
	}

	virtual BoundingBox calculateBoundingBox() {
		BoundingBox BB;
		bg::append(BB.outer(), point_t(posX - width / 2, posY - height / 2));
		bg::append(BB.outer(), point_t(posX + width / 2, posY - height / 2));
		bg::append(BB.outer(), point_t(posX + width / 2, posY + height / 2));
		bg::append(BB.outer(), point_t(posX - width / 2, posY + height / 2));
		bg::append(BB.outer(), point_t(posX - width / 2, posY - height / 2));

		return BB;
	}
};

template<typename Functor>
class Button<Functor, void> : public IRenderable {
public:
	unsigned int height;
	unsigned int width;
	Functor func;

	Button() {}
	Button(int x, int y, unsigned int h, unsigned int w) : posX(x), posY(y), height(h), width(w) {}
	Button(int x, int y, unsigned int h, unsigned int w, Functor func) : posX(x), posY(y), height(h), width(w), func(func) {}
	virtual ~Button() {}

	virtual void onMouseClick() override {
		func(); //TODO Untested semantics, not 100% sure one this one
	}

	virtual AbstractRender& getRender() override {
		static RenderBB render{sf::Color(100, 100, 100)};
		return render;
	}

	virtual BoundingBox calculateBoundingBox() {
		BoundingBox BB;
		bg::append(BB.outer(), point_t(posX - width / 2, posY - height / 2));
		bg::append(BB.outer(), point_t(posX + width / 2, posY - height / 2));
		bg::append(BB.outer(), point_t(posX + width / 2, posY + height / 2));
		bg::append(BB.outer(), point_t(posX - width / 2, posY + height / 2));
		bg::append(BB.outer(), point_t(posX - width / 2, posY - height / 2));

		return BB;
	}
};

