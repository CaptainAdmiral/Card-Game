#include "StandardGamePhases.h"

StandardGamePhases::GamePhase_Start::GamePhase_Start(GameComponents &components) : AbstractGamePhase(GamePhase::GAME_START, components) {}

StandardGamePhases::GamePhase_Start::~GamePhase_Start() {
	for (int i = 0; i < 5; i++) {
		//TODO decide whether to use the standard draw function which triggers draw events or not
		gameComponents.player.draw();
	}
}

void StandardGamePhases::GamePhase_Start::doPhase() {}

StandardGamePhases::GamePhase_Draw::GamePhase_Draw(GameComponents &components) : AbstractGamePhase(GamePhase::DRAW, components) {}

StandardGamePhases::GamePhase_Draw::~GamePhase_Draw() {}

void StandardGamePhases::GamePhase_Draw::doPhase() {
	gameComponents.player.draw();
}

StandardGamePhases::GamePhase_Planning::GamePhase_Planning(GameComponents &components) : AbstractGamePhase(GamePhase::PLANNING, components) {}

StandardGamePhases::GamePhase_Planning::~GamePhase_Planning() {}

void StandardGamePhases::GamePhase_Planning::doPhase() {}


StandardGamePhases::GamePhase_Action::GamePhase_Action(GameComponents &components) : AbstractGamePhase(GamePhase::ACTION, components){}

StandardGamePhases::GamePhase_Action::~GamePhase_Action() {}

void StandardGamePhases::GamePhase_Action::doPhase() {}


StandardGamePhases::GamePhase_End::GamePhase_End(GameComponents &components) : AbstractGamePhase(GamePhase::END, components) {}

StandardGamePhases::GamePhase_End::~GamePhase_End() {}

void StandardGamePhases::GamePhase_End::doPhase() {}

StandardGamePhases::GamePhase_Finish::GamePhase_Finish(GameComponents &components) : AbstractGamePhase(GamePhase::GAME_FINISH, components) {}

StandardGamePhases::GamePhase_Finish::~GamePhase_Finish() {}

void StandardGamePhases::GamePhase_Finish::doPhase() {}