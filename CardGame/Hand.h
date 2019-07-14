#pragma once
#include "AbstractCardContainer.h"

class Hand : public AbstractCardContainer {
public:
	Hand();
	~Hand();

	virtual CardPtr card_out() override;
};

