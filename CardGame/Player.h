#pragma once
#include "Settings.h"
#include "deck.h"
#include "hand.h"
#include "field.h"
#include "action.h"
#include <tuple>

typedef std::vector<Action> ActionList;

class Player {
public:
	std::tuple<int, int, int> color{100, 100, 100};

	Deck deck{*this};
	Hand hand{Settings::General::DEFAULT_WIDTH/2.0f, Settings::General::DEFAULT_HEIGHT - Settings::UI::handHeight/2};

	//TODO Refreshed on new turn event
	Field planningField; //Player specific planning phase field
	ActionList plannedActions; //Vector of actions the player has taken on the planning field
	unsigned int summons; //Player summons this turn
	unsigned int moves; //Player moves this turn

	Player();
	Player(int r, int g, int b);
	virtual ~Player();

	void setColor(int r, int g, int b);
	std::tuple<int, int, int> getColor();

	virtual void draw();
	virtual void draw(int);

	virtual void setVisible(bool vis);
};

