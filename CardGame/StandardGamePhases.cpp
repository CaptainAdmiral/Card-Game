#include "StandardGamePhases.h"

StandardGamePhases::GamePhase_Draw::GamePhase_Draw(GameComponents &gameComponents) : AbstractGamePhase(GamePhase::DRAW), gameComponents(gameComponents) {}

StandardGamePhases::GamePhase_Draw::~GamePhase_Draw() {}

void StandardGamePhases::GamePhase_Draw::doPhase() {
	//Pre phase event
	gameComponents.player.draw();
	//Post phase event
}


StandardGamePhases::GamePhase_Planning::GamePhase_Planning(GameComponents &gameComponents) : AbstractGamePhase(GamePhase::PLANNING), gameComponents(gameComponents) {}

StandardGamePhases::GamePhase_Planning::~GamePhase_Planning() {}

void StandardGamePhases::GamePhase_Planning::doPhase() {}


StandardGamePhases::GamePhase_Action::GamePhase_Action(GameComponents &gameComponents) : AbstractGamePhase(GamePhase::ACTION), gameComponents(gameComponents) {}

StandardGamePhases::GamePhase_Action::~GamePhase_Action() {}

void StandardGamePhases::GamePhase_Action::doPhase() {}


StandardGamePhases::GamePhase_End::GamePhase_End(GameComponents &gameComponents) : AbstractGamePhase(GamePhase::END), gameComponents(gameComponents) {}

StandardGamePhases::GamePhase_End::~GamePhase_End() {}

void StandardGamePhases::GamePhase_End::doPhase() {}
