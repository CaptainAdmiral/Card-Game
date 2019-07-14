#pragma once
#include "ICardContainer.h"

class Slot : ICardContainer {
public:
	Slot();
	~Slot();

	CardPtr contents;

	//Assert slot is empty (use isEmpty() or hasSpace() to check)
	virtual void card_in(CardPtr) override;
	virtual CardPtr card_out() override;
	virtual CardPtr card_out(Card&) override;
	virtual bool hasSpace() override;
	virtual bool isEmpty() override;
	virtual bool contains(Card&) override;
};