#include "StandardGamePhases.h"
#include "PhaseCycle.h"
#include "MouseHandler.h"
#include "RenderManager.h"
#include "RenderType.h"

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
	gameComponents.field.displayAsAfterimage(false);
}

void StandardGamePhases::GamePhase_Planning::doPhase() {
	if(draggedCard != nullptr) {
		draggedCard->setPos(mouseX, mouseY);
	}
}

void StandardGamePhases::GamePhase_Planning::onMousePressed(int x, int y) {
	if((*turnCycle->currentPhase).get() != this) return;
	IRenderable *renderable = RenderManager::instance().getHit(x, y);

	if(renderable != nullptr && renderable->getType() == RenderType::CARD) {
		draggedCard = static_cast<Card*>(renderable);
		RenderManager::instance().bringToFront(draggedCard);
		draggedReturnX = draggedCard->getPosX();
		draggedReturnY = draggedCard->getPosY();
	}
}

void StandardGamePhases::GamePhase_Planning::onMouseReleased(int x, int y) {
	if((*turnCycle->currentPhase).get() != this) return;
	if(draggedCard == nullptr) return;
	IRenderable *renderable = RenderManager::instance().getHitWithIgnore(x, y, draggedCard);

	if(renderable != nullptr && renderable->getType() == RenderType::SLOT) {
		Slot &slot = *static_cast<Slot*>(renderable);
		if(draggedCard->container->giveCardTo(static_cast<ICardContainer&>(slot), *draggedCard)) {
			draggedCard->setPos(slot.getPosX(), slot.getPosY());
			draggedReturnX = draggedCard->getPosX();
			draggedReturnY = draggedCard->getPosY();
		}
	}

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