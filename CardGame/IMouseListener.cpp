#include "IMouseListener.h"
#include "MouseHandler.h"

IMouseListener::IMouseListener() {
	MouseHandler::subscribe(this);
}

IMouseListener::IMouseListener(const IMouseListener &) {
	MouseHandler::subscribe(this);
}

IMouseListener::~IMouseListener() {
	MouseHandler::unsubscribe(this);
}
