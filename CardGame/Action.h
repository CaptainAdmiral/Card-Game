#pragma once
#include <vector>

class Card;
class Slot;

struct Action {
public:
	enum Type {
		MOVE,
		MOVE_FAIL,
		ATTACK,
		SUMMON,
	};

	const Type type;

	struct Move {
		Card &card;
		Slot &slotTo;

		Move(Card &card, Slot &slotTo) : card(card), slotTo(slotTo) {}
	};

	struct Attack {
		Card &card;
		Slot &target;

		Attack(Card& card, Slot &target) : card(card), target(target) {}
	};

	struct Summon {
		Card &card;
		Slot &slot;

		Summon(Card &card, Slot &slot) : card(card), slot(slot) {}
	};

	const Action::Move getMove() {
		return action.move;
	}

	const Action::Attack getAttack() {
		return action.attack;
	}

	const Action::Summon getSummon() {
		return action.summon;
	}

	Action(Move action) : type(MOVE), action(action) {}
	Action(Attack action) : type(ATTACK), action(action) {}
	Action(Summon action) : type(SUMMON), action(action) {}

private:
	union ActionUnion {
		Move move;
		Attack attack;
		Summon summon;

		ActionUnion(Action::Move action) : move(action) {}
		ActionUnion(Action::Attack action) : attack(action) {}
		ActionUnion(Action::Summon action) : summon(action) {}
	};

	const ActionUnion action;
};