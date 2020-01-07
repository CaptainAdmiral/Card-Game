#include "StandardGamePhases.h"
#include "PhaseCycle.h"
#include "iostream"
#include "MouseHandler.h"

StandardGamePhases::GamePhase_Start::GamePhase_Start(GameComponents &components, PhaseCycle *turnCycle) : AbstractGamePhase(GamePhase::GAME_START, components, turnCycle) {}

StandardGamePhases::GamePhase_Start::~GamePhase_Start() {}

void StandardGamePhases::GamePhase_Start::doPhase() {
	//TODO decide whether to use the standard draw function which triggers draw events or not
	gameComponents.player.draw(5);
	turnCycle->removePhase(this);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::GamePhase_Draw::GamePhase_Draw(GameComponents &components) : AbstractGamePhase(GamePhase::DRAW, components) {}

StandardGamePhases::GamePhase_Draw::~GamePhase_Draw() {}

void StandardGamePhases::GamePhase_Draw::doPhase() {
	gameComponents.player.draw();
	this->setFinished();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::GamePhase_Planning::GamePhase_Planning(GameComponents &components) : AbstractGamePhase(GamePhase::PLANNING, components) {}

StandardGamePhases::GamePhase_Planning::~GamePhase_Planning() {

}

void StandardGamePhases::GamePhase_Planning::doPhase() {
	
}

void StandardGamePhases::GamePhase_Planning::onMouseReleased(int x, int y) {
	
}

void StandardGamePhases::GamePhase_Planning::onMousePressed(int x, int y) {
	
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::GamePhase_Action::GamePhase_Action(GameComponents &components) : AbstractGamePhase(GamePhase::ACTION, components){}

StandardGamePhases::GamePhase_Action::~GamePhase_Action() {}

void StandardGamePhases::GamePhase_Action::doPhase() {}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::GamePhase_End::GamePhase_End(GameComponents &components) : AbstractGamePhase(GamePhase::END, components) {}

StandardGamePhases::GamePhase_End::~GamePhase_End() {}

void StandardGamePhases::GamePhase_End::doPhase() {}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::GamePhase_Finish::GamePhase_Finish(GameComponents &components) : AbstractGamePhase(GamePhase::GAME_FINISH, components) {}

StandardGamePhases::GamePhase_Finish::~GamePhase_Finish() {}

void StandardGamePhases::GamePhase_Finish::doPhase() {}