#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class IMouseListener;
class Event;

namespace MouseHandler {
	static std::vector<IMouseListener*> observers;

	void subscribe(IMouseListener *listener);

	void unsubscribe(IMouseListener *listener);
	
	void postEvent(sf::Event &e);
};

