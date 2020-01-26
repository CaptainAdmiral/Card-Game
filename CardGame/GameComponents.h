#pragma once
#include "Player.h"
#include "Opponent.h"
#include "Field.h"

struct GameComponents {
	Player player{30, 180, 30};
	Player player2{180, 30, 30};
	Opponent opponent;
	Field field;
};

