#include "StandardGamePhases.h"
#include "PhaseCycle.h"
#include "MouseHandler.h"
#include "RenderManager.h"
#include "Settings.h"
#include "ValidateSummonEvent.h"
#include "ValidateMoveEvent.h"
#include "EventHandler.h"

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
	button.setPos(Settings::General::DEFAULT_WIDTH / 2, Settings::General::DEFAULT_HEIGHT*0.04);
	button.width = Settings::General::DEFAULT_WIDTH*0.4;
	button.height = Settings::General::DEFAULT_HEIGHT*0.04;
	button.func = &AbstractGamePhase::setFinished;
	button.instance = this;
	button.updateBoundingBox();

	turnCycle->sharedInfo["planningField"] = field.get();
}

StandardGamePhases::GamePhase_Planning::~GamePhase_Planning() {
	turnCycle->sharedInfo.erase("planningField");
}

void StandardGamePhases::GamePhase_Planning::onPhaseStart() {
	field = std::make_unique<Field>(gameComponents.field);
	gameComponents.field.displayAsAfterimage(false);

	summons = 0;
	for(auto const &move : cardMoves) {
		cardMoves[move.first] = 0;
	}
}

void StandardGamePhases::GamePhase_Planning::doPhase() {
	if(draggedCard != nullptr) {
		draggedCard->setPos(mouseX, mouseY);
	}
}

void StandardGamePhases::GamePhase_Planning::onMousePressed(int x, int y) {
	if((*turnCycle->currentPhase).get() != this) return;
	IRenderable *renderable = RenderManager::instance().getHit(x, y);

	if(renderable != nullptr && renderable->getType() == GameObjectType::CARD) {
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

	if(renderable != nullptr && renderable->getType() == GameObjectType::SLOT) {
		Slot &slot = *static_cast<Slot*>(renderable);

		if(draggedCard->container->type() == Hand::TYPE) {
			ValidateSummonEvent e(*draggedCard, slot, summons);
			EventHandler::postEvent(e);

			if(e.isValid && draggedCard->container->giveCardTo(static_cast<ICardContainer&>(slot), *draggedCard)) {
				draggedCard->setPos(slot.getPosX(), slot.getPosY());
				draggedReturnX = draggedCard->getPosX();
				draggedReturnY = draggedCard->getPosY();
				cardMoves[draggedCard]++;
				summons++;
			}
		} else if(draggedCard->container->type() == Slot::TYPE) {
			ValidateMoveEvent e(*draggedCard, slot, cardMoves[draggedCard]);
			EventHandler::postEvent(e);

			if(e.isValid && draggedCard->container->giveCardTo(static_cast<ICardContainer&>(slot), *draggedCard)) {
				draggedCard->setPos(slot.getPosX(), slot.getPosY());
				draggedReturnX = draggedCard->getPosX();
				draggedReturnY = draggedCard->getPosY();
				cardMoves[draggedCard]++;
			}
		}
	}

	draggedCard->setPos(draggedReturnX, draggedReturnY);
	draggedCard = nullptr;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::GamePhase_Action::GamePhase_Action(GameComponents &components) : AbstractGamePhase(GamePhase::ACTION, components){}

StandardGamePhases::GamePhase_Action::~GamePhase_Action() {}

void StandardGamePhases::GamePhase_Action::doPhase() {
	setFinished();
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::GamePhase_End::GamePhase_End(GameComponents &components) : AbstractGamePhase(GamePhase::END, components) {}

StandardGamePhases::GamePhase_End::~GamePhase_End() {}

void StandardGamePhases::GamePhase_End::doPhase() {}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::GamePhase_Finish::GamePhase_Finish(GameComponents &components) : AbstractGamePhase(GamePhase::GAME_FINISH, components) {}

StandardGamePhases::GamePhase_Finish::~GamePhase_Finish() {}

void StandardGamePhases::GamePhase_Finish::doPhase() {}