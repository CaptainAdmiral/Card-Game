#pragma once
#include "ICardContainer.h"
#include <vector>

class Deck : public ICardContainer {
public:
	Deck();
	~Deck();

	virtual void card_in(CardPtr) override;

	virtual CardPtr card_out() override;

	virtual CardPtr card_out(Card&) override;

	virtual bool hasSpace() override;

	virtual bool contains(Card&) override;

	virtual bool isEmpty() override;
};

