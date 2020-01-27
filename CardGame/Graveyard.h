#pragma once
#include "AbstractCardContainer.h"

class Graveyard : public AbstractCardContainer {
public:
	Graveyard();
	~Graveyard();

	virtual GameObjectType type() override;
};

