#pragma once
#include "ICardContainer.h"
#include <vector>

class Player;

class Deck : public ICardContainer {
public:
	Player &owner;

	Deck(Player &player);
	~Deck();

	virtual void card_in(CardPtr) override;

	virtual CardPtr card_out() override;

	virtual CardPtr card_out(Card&) override;

	virtual bool hasSpace() override;

	virtual bool contains(Card&) override;

	virtual bool isEmpty() override;

	virtual GameObjectType type() override {
		return GameObjectType::DECK;
	}
};

