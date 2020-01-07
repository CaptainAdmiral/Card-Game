#pragma once

class IMouseListener {
public:
	IMouseListener();
	IMouseListener(const IMouseListener&);
	~IMouseListener();

	virtual void onMouseReleased(int x, int y) = 0;
	virtual void onMousePressed(int x, int y) = 0;
};