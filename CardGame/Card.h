#pragma once
#include "IRenderable.h"

class ICardContainer;

class Card : public IRenderable {
public:
	ICardContainer *container = nullptr;

	bool isAfterimage = false;
	bool isInSlot = false;

	Card();
	~Card();

	AbstractRender &getRender() override;

	virtual BoundingBox calculateBoundingBox() override;

	virtual RenderType getType() override;

	//TODO replace with one of the following hashmaps:
	//std::unordered_map<std::String, unsigned short>
	//std::unordered_map<std::String, BoolShortUnion union>
	//std::unordered_map<std::String, std::any>
	struct Properties {
	public:
		Properties() {};
		~Properties() {};

		enum type{Unit, Spell};

		unsigned int atk=0;
		unsigned int ctr = 0; //TODO make sure counter is never lower than defense
		unsigned int def=0;
		unsigned int speed=1;
		unsigned int range=1;

		Properties &setAtk(int);

		Properties &setCtr(int);

		Properties &setDef(int);

		Properties &setSpeed(int);

		Properties &setRange(int);
	};

	Properties properties;

	Card(Properties props);
};