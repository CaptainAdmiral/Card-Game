#pragma once
#include <vector>

class Card;
class Slot;

//A namespace of free functions is used here instead of putting the implementation in the classes that the behavior refers to because most of
//the game objects behaviours are defined by the game phase they're in, and putting common game actions here is much more intuitive when linking
//card texts to the functions required to execute common game actions than putting them in the game phases that define those actions.
namespace Actions {
	void move(Card &card, Slot &slot);

	void summon(Card &card, Slot &slot);

	void attackSlot(Slot &slot, std::vector<Card*> attackers);

	void attack(Card &attacker, Card &attacked);
};

