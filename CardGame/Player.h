#pragma once
#include "deck.h"
#include "hand.h"

class Player {
public:
	Deck deck;
	Hand hand;

	Player();
	virtual ~Player();

	virtual void draw();

	virtual void draw(int);
};

