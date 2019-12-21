#pragma once
#include <SFML/Graphics.hpp>

class RenderWrapper {
	typedef sf::RenderWindow RW;

public:

	RenderWrapper(RW &window) : window(&window) {}

	//Returns the unwrapped instance of render window
	RW &unwrap() const {
		return *window;
	}

	//Indirect call to RenderWindow draw()
	void draw(const sf::Drawable &drawable) {
		window->draw(drawable);
	}

	//Returns the size of the window
	sf::Vector2u getSize() {
		return window->getSize();
	}

	unsigned int getHeight() {
		return getSize().y;
	}

	unsigned int getWidth() {
		return getSize().x;
	}

private:
RW *window;
};

