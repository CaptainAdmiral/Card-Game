#include "StandardGamePhases.h"
#include "PhaseCycle.h"
#include "MouseHandler.h"
#include "RenderManager.h"
#include "Settings.h"
#include "ValidateSummonEvent.h"
#include "ValidateMoveEvent.h"
#include "EventHandler.h"
#include "StandardGamePhaseData.h"

StandardGamePhases::Start::Start(GameComponents &components, Player *player, PhaseCycle *turnCycle) : AbstractGamePhase(GamePhase::GAME_START, components, player, turnCycle) {}

StandardGamePhases::Start::~Start() {}

void StandardGamePhases::Start::doPhase() {
	//TODO decide whether to use the standard draw function which triggers draw events or not
	player->draw(5);

	turnCycle->removePhase(this);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::Draw::Draw(GameComponents &components, Player* player) : AbstractGamePhase(GamePhase::DRAW, components, player) {}

StandardGamePhases::Draw::~Draw() {}

void StandardGamePhases::Draw::doPhase() {
	gameComponents.player.draw();
	this->setFinished();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::Planning::Planning(GameComponents &components, Player* player, PhaseCycle *turnCycle) : AbstractGamePhase(GamePhase::PLANNING, components, player, turnCycle) {
	button.width = Settings::General::DEFAULT_WIDTH*0.4;
	button.height = Settings::General::DEFAULT_HEIGHT*0.04;
	button.func = &AbstractGamePhase::setFinished;
	button.instance = this;
	button.setPos(Settings::General::DEFAULT_WIDTH / 2, Settings::General::DEFAULT_HEIGHT*0.04);
}

StandardGamePhases::Planning::~Planning() {}

void StandardGamePhases::Planning::onPhaseStart() {
	//TODO move begining of turn cleanup to new turn event in player class

	player->planningField = gameComponents.field;
	player->plannedActions.clear();
	player->planningField.for_each_card([](Card& card) {card.justSummoned = false; });
	player->planningField.for_each_card([](Card& card) {card.moves = 0; });
	player->summons = 0;
	player->moves = 0;

	gameComponents.field.displayAsAfterimage(true);
	player->planningField.bringCardsToFront();
	button.setVisible(true);
}

void StandardGamePhases::Planning::onPhaseEnd() {
	gameComponents.field = player->planningField;
	gameComponents.field.displayAsAfterimage(false);
	button.setVisible(false);
}

void StandardGamePhases::Planning::doPhase() {
	if(draggedCard != nullptr) {
		draggedCard->setPos(mouseX, mouseY);
	}
}

void StandardGamePhases::Planning::onMousePressed(int x, int y) {
	if(turnCycle->getCurrentPhase().get() != this) return;
	IRenderable *renderable = RenderManager::instance().getHit(x, y);

	if(renderable != nullptr && renderable->getType() == GameObjectType::CARD) {
		draggedCard = static_cast<Card*>(renderable);
		RenderManager::instance().bringToFront(draggedCard);
		draggedReturnX = draggedCard->getPosX();
		draggedReturnY = draggedCard->getPosY();
	}
}

void StandardGamePhases::Planning::onMouseReleased(int x, int y) {
	if(turnCycle->getCurrentPhase().get() != this) return;
	if(draggedCard == nullptr) return;
	IRenderable *renderable = RenderManager::instance().getHitWithIgnore(x, y, draggedCard);

	if(renderable != nullptr && renderable->getType() == GameObjectType::SLOT) {
		Slot &slot = *static_cast<Slot*>(renderable);

		if(draggedCard->container->type() == Hand::TYPE) {
			ValidateSummonEvent e(*draggedCard, slot);
			EventHandler::postEvent(e);

			if(e.isValid && draggedCard->container->giveCardTo(static_cast<ICardContainer&>(slot), *draggedCard)) {
				draggedCard->setPos(slot.getPosX(), slot.getPosY());
				draggedReturnX = draggedCard->getPosX();
				draggedReturnY = draggedCard->getPosY();

				player->plannedActions.emplace_back<Action>(Action::Summon(*draggedCard, slot));
				player->summons++;
				draggedCard->justSummoned = true;
			}
		} else if(draggedCard->container->type() == Slot::TYPE) {
			ValidateMoveEvent e(*draggedCard, slot);
			EventHandler::postEvent(e);

			if(e.isValid && draggedCard->container->giveCardTo(static_cast<ICardContainer&>(slot), *draggedCard)) {
				draggedCard->setPos(slot.getPosX(), slot.getPosY());
				draggedReturnX = draggedCard->getPosX();
				draggedReturnY = draggedCard->getPosY();

				player->plannedActions.emplace_back<Action>(Action::Move(*draggedCard, slot));
				player->moves++;
				draggedCard->moves++;
			}
		}
	}

	draggedCard->setPos(draggedReturnX, draggedReturnY);
	draggedCard = nullptr;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::Resolution::Resolution(GameComponents &components) : AbstractGamePhase(GamePhase::ACTION, components){}

StandardGamePhases::Resolution::~Resolution() {}

void StandardGamePhases::Resolution::doPhase() {
	setFinished();
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::End::End(GameComponents &components) : AbstractGamePhase(GamePhase::END, components) {}

StandardGamePhases::End::~End() {}

void StandardGamePhases::End::doPhase() {}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::Finish::Finish(GameComponents &components) : AbstractGamePhase(GamePhase::GAME_FINISH, components) {}

StandardGamePhases::Finish::~Finish() {}

void StandardGamePhases::Finish::doPhase() {}