#include "StandardGamePhases.h"

StandardGamePhases::GamePhase_Start::GamePhase_Start(GameComponents &components, TurnCycle *turnCycle) : AbstractGamePhase(GamePhase::GAME_START, components, turnCycle) {}

StandardGamePhases::GamePhase_Start::~GamePhase_Start() {}

void StandardGamePhases::GamePhase_Start::doPhase() {
	//TODO decide whether to use the standard draw function which triggers draw events or not
	gameComponents.player.draw(5);

	turnCycle->erase(std::find_if(turnCycle->begin(), turnCycle->end(), [&](std::unique_ptr<AbstractGamePhase> const &phase) {
		return phase.get() == this;
	}));
	//TODO current phase iterator needs to be incremented before find-erase to avoid invalidation
}

StandardGamePhases::GamePhase_Draw::GamePhase_Draw(GameComponents &components) : AbstractGamePhase(GamePhase::DRAW, components) {}

StandardGamePhases::GamePhase_Draw::~GamePhase_Draw() {}

void StandardGamePhases::GamePhase_Draw::doPhase() {
	gameComponents.player.draw();
	this->setFinished();
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