#pragma once

class IMouseListener {
public:
	IMouseListener();
	IMouseListener(const IMouseListener&);
	IMouseListener &operator=(const IMouseListener&);
	~IMouseListener();

	int mouseX;
	int mouseY;

	virtual void onMousePressed(int x, int y) = 0;
	virtual void onMouseReleased(int x, int y) = 0;
	virtual void onMouseMoved(int x, int y)  {};
};