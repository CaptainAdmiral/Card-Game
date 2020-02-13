#include "GamePhasePlanning.h"
#include "PhaseCycle.h"
#include "MouseHandler.h"
#include "RenderManager.h"
#include "Settings.h"
#include "ValidateSummonEvent.h"
#include "ValidateMoveEvent.h"
#include "EventHandler.h"
#include "Actions.h"

GamePhasePlanning::GamePhasePlanning(GameComponents &components, Player* player, PhaseCycle *turnCycle) : AbstractGamePhase(GamePhase::PLANNING, components, player, turnCycle) {
	button.width = Settings::General::DEFAULT_WIDTH*0.4;
	button.height = Settings::General::DEFAULT_HEIGHT*0.04;
	button.func = &AbstractGamePhase::setFinished;
	button.instance = this;
	button.setPos(Settings::General::DEFAULT_WIDTH / 2, Settings::General::DEFAULT_HEIGHT*0.04);
	button.setVisible(false);
}

GamePhasePlanning::~GamePhasePlanning() {}

void GamePhasePlanning::onPhaseStart() {
	//TODO move begining of turn cleanup to buff system using new turn event

	player->planningField = gameComponents.field;
	player->plannedActions.clear();
	player->planningField.for_each_card([](Card& card) {card.justSummoned = false; });
	player->planningField.for_each_card([](Card& card) {card.moves = 0; });

	gameComponents.field.displayAsAfterimage(true);
	player->planningField.bringCardsToFront();

	player->planningField.for_each_card([](Card& card) {card.setVisible(true); });
	player->planningField.for_each_slot([](Slot& slot) {slot.setVisible(true); });
	button.setVisible(true);
	player->setVisible(true);
}

void GamePhasePlanning::onPhaseEnd() {
	player->planningField.for_each_card([](Card& card) {card.setVisible(false); });
	player->planningField.for_each_slot([](Slot& slot) {slot.setVisible(false); });

	gameComponents.field.displayAsAfterimage(false);
	button.setVisible(false);
	player->setVisible(false);
}

void GamePhasePlanning::doPhase() {
	if(draggedCard != nullptr) {
		draggedCard->setPos(mouseX, mouseY);
	}
}

void GamePhasePlanning::onMousePressed(int x, int y) {
	if(turnCycle->getCurrentPhase().get() != this) return;
	IRenderable *renderable = RenderManager::instance().getHit(x, y);

	if(renderable != nullptr && renderable->getType() == GameObjectType::CARD && static_cast<Card*>(renderable)->owner == const_cast<Player*>(player)) {
		draggedCard = static_cast<Card*>(renderable);
		RenderManager::instance().bringToFront(draggedCard);
		draggedReturnX = draggedCard->getPosX();
		draggedReturnY = draggedCard->getPosY();
	}
}

void GamePhasePlanning::onMouseReleased(int x, int y) {
	if(turnCycle->getCurrentPhase().get() != this) return;
	if(draggedCard == nullptr) return;
	IRenderable *renderable = RenderManager::instance().getHitWithIgnore(x, y, draggedCard);

	if(renderable != nullptr && renderable->getType() == GameObjectType::SLOT) {
		Slot &slot = *static_cast<Slot*>(renderable);

		if(draggedCard->container->type() == Hand::TYPE) {
			ValidateSummonEvent e(*draggedCard, slot);
			EventHandler::postEvent(e);

			if(e.isValid) {
				Actions::summon(*draggedCard, slot);
				draggedReturnX = slot.getPosX();
				draggedReturnY = slot.getPosY();

				player->plannedActions.emplace_back<Action>(Action::Summon(*draggedCard, std::make_pair(slot.row, slot.col)));
				draggedCard->justSummoned = true;
			}
		}
		else if(draggedCard->container->type() == Slot::TYPE) {
			ValidateMoveEvent e(*draggedCard, slot);
			EventHandler::postEvent(e);

			if(e.isValid) {
				Slot &slotFrom = *static_cast<Slot*>(draggedCard->container);

				Actions::move(*draggedCard, slot);
				draggedReturnX = slot.getPosX();
				draggedReturnY = slot.getPosY();

				player->plannedActions.emplace_back<Action>(Action::Attack(std::make_pair(slotFrom.row, slotFrom.col), std::make_pair(slot.row, slot.col)));
				player->plannedActions.emplace_back<Action>(Action::Move(std::make_pair(slotFrom.row, slotFrom.col), std::make_pair(slot.row, slot.col)));
				draggedCard->moves++;
			}
		}
	}

	draggedCard->setPos(draggedReturnX, draggedReturnY);
	draggedCard = nullptr;
}