#include "MouseHandler.h"
#include "IMouseListener.h"
#include <algorithm>


void MouseHandler::subscribe(IMouseListener *listener) {
	observers.push_back(listener);
}

void MouseHandler::unsubscribe(IMouseListener *listener) {
	observers.erase(std::remove(observers.begin(), observers.end(), listener), observers.end());
}

void MouseHandler::postEvent(sf::Event &e) {
	int x;
	int y;
	switch(e.type) {
	case sf::Event::MouseButtonPressed:


		x = e.mouseButton.x;
		y = e.mouseButton.y;
		for(IMouseListener *observer : observers) {
			observer->onMousePressed(x,y);
		}
		break;
	case sf::Event::MouseButtonReleased:
		x = e.mouseButton.x;
		y = e.mouseButton.y;
		for(IMouseListener *observer : observers) {
			observer->onMouseReleased(x,y);
		}
		break;
	}
}
