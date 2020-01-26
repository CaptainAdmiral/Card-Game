#pragma once
#include "IRenderable.h"

class ICardContainer;
class Player;

class Card : public IRenderable {
public:
	//Data to be represented by buffs
	unsigned int moves = 0;
	bool justSummoned = false;

	bool isCountering = true;
	//fortificationBuffer = 0;
	/////////////////////////////////

	ICardContainer *container = nullptr;
	Player *owner = nullptr;

	bool isAfterimage = false;
	bool isInSlot = false;

	Card();
	Card(Player &player);
	~Card();

	AbstractRender &getRender() override;

	virtual BoundingBox calculateBoundingBox() override;

	virtual GameObjectType getType() override;

	virtual bool isClickable() override;

	//TODO replace with one of the following hashmaps:
	//std::unordered_map<std::String, unsigned short>
	//std::unordered_map<std::String, BoolShortUnion union>
	//std::unordered_map<std::String, std::any>
	struct Properties {
	public:
		Properties() {};
		~Properties() {};

		enum Type{UNIT, SPELL};

		int atk=0;
		int hp = 0;
		int ctr=0;
		int speed=1;
		int range=1;

		Properties &setAtk(int);
		Properties &setHp(int);
		Properties &setCtr(int);
		Properties &setSpeed(int);
		Properties &setRange(int);
	};

	Properties properties;
	Card(Properties props);
};