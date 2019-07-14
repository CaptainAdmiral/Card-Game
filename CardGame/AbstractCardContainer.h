#pragma once
#include "ICardContainer.h"
#include <vector>
#include <algorithm>

typedef std::vector<CardPtr> CardCollection;

class AbstractCardContainer : public ICardContainer {
public:
	virtual ~AbstractCardContainer() {}

	CardCollection contents;

	//Request to move unique pointer into card container
	//Return success
	virtual void card_in(CardPtr) override;

	virtual CardPtr card_out() override = 0;

	//Removes and returns a single specified card from the contents of the card container
	//Return unique pointer to removed card
	virtual CardPtr card_out(Card&) override;

	virtual bool hasSpace() override;

	virtual bool isEmpty() override;

	virtual bool contains(Card&) override;
};

