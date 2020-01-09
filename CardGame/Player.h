#pragma once
#include "Settings.h"
#include "deck.h"
#include "hand.h"

class Player {
public:
	Deck deck;
	Hand hand{Settings::General::DEFAULT_WIDTH/2.0f, Settings::General::DEFAULT_HEIGHT - Settings::UI::handHeight/2};

	Player();
	virtual ~Player();

	virtual void draw();

	virtual void draw(int);
};

