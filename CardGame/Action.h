#pragma once
#include <vector>

typedef std::pair<unsigned int, unsigned int> Coordinate;

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
		Coordinate from;
		Coordinate to;

		Move(Coordinate from, Coordinate to) : from(from), to(to) {}
	};

	struct Attack {
		Coordinate attacker;
		Coordinate attacked;

		Attack(Coordinate attacker, Coordinate attacked) : attacker(attacker), attacked(attacked) {}
	};

	struct Summon {
		Card &card;
		Coordinate to;

		Summon(Card &card, Coordinate to) : card(card), to(to) {}
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