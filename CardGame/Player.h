#pragma once
#include "Settings.h"
#include "deck.h"
#include "hand.h"
#include "field.h"
#include "action.h"

typedef std::vector<Action> ActionList;

class Player {
public:
	Deck deck{*this};
	Hand hand{Settings::General::DEFAULT_WIDTH/2.0f, Settings::General::DEFAULT_HEIGHT - Settings::UI::handHeight/2};

	//TODO Refreshed on new turn event
	Field planningField; //Player specific planning phase field
	ActionList plannedActions; //Vector of actions the player has taken on the planning field
	unsigned int summons; //Player summons this turn
	unsigned int moves; //Player moves this turn

	Player();
	virtual ~Player();

	virtual void draw();

	virtual void draw(int);

	virtual void setVisible(bool vis);
};

