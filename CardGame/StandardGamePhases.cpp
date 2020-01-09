#include "StandardGamePhases.h"
#include "PhaseCycle.h"
#include "MouseHandler.h"
#include "RenderManager.h"
#include <iostream>

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



StandardGamePhases::GamePhase_Planning::GamePhase_Planning(GameComponents &components, PhaseCycle *turnCycle) : AbstractGamePhase(GamePhase::PLANNING, components, turnCycle) {
	turnCycle->sharedInfo["planningField"] = field.get();
}

StandardGamePhases::GamePhase_Planning::~GamePhase_Planning() {
	turnCycle->sharedInfo.erase("planningField");
}

void StandardGamePhases::GamePhase_Planning::onPhaseStart() {
	field = std::make_unique<Field>(gameComponents.field);
}

void StandardGamePhases::GamePhase_Planning::doPhase() {
	if(draggedCard != nullptr) {
		draggedCard->setPos(mouseX, mouseY);
	}
}

void StandardGamePhases::GamePhase_Planning::onMousePressed(int x, int y) {
	if((*turnCycle->currentPhase).get() != this) return;
	IRenderable *renderable = RenderManager::instance().getClicked(x, y);
	if(renderable != nullptr) {
		std::cout << renderable->getType();
		std::cout << "\n";
		std::cout << Slot::TYPE << " " << Card::TYPE << "\n";
	}
	if(renderable != nullptr && renderable->getType() == Card::TYPE) {
		draggedCard = static_cast<Card*>(renderable);
		draggedReturnX = draggedCard->getPosX();
		draggedReturnY = draggedCard->getPosY();
	}
}

void StandardGamePhases::GamePhase_Planning::onMouseReleased(int x, int y) {
	if((*turnCycle->currentPhase).get() != this) return;
	if(draggedCard == nullptr) return;
	draggedCard->setPos(draggedReturnX, draggedReturnY);
	draggedCard = nullptr;
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