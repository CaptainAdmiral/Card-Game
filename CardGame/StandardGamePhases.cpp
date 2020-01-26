#include "StandardGamePhases.h"
#include "PhaseCycle.h"

StandardGamePhases::Start::Start(GameComponents &components, Player *player, PhaseCycle *turnCycle) : AbstractGamePhase(GamePhase::GAME_START, components, player, turnCycle) {}

StandardGamePhases::Start::~Start() {}

void StandardGamePhases::Start::doPhase() {
	//TODO decide whether to use the standard draw function which triggers draw events or not
	player->draw(5);

	gameComponents.field.for_each_slot([&](Slot &slot) {
		if(slot.properties.type == Slot::Properties::BASE || slot.properties.type == Slot::Properties::SUMMON || slot.properties.type == Slot::Properties::MANA) {
			if(slot.row > 5) {
				slot.properties.setController(&gameComponents.player2);
			}
			else if(slot.row < 5) {
				slot.properties.setController(&gameComponents.player);
			}
		}
	});

	turnCycle->removePhase(this);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::Draw::Draw(GameComponents &components, Player* player) : AbstractGamePhase(GamePhase::DRAW, components, player) {}

StandardGamePhases::Draw::~Draw() {}

void StandardGamePhases::Draw::doPhase() {
	player->draw();
	this->setFinished();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::End::End(GameComponents &components) : AbstractGamePhase(GamePhase::END, components) {}

StandardGamePhases::End::~End() {}

void StandardGamePhases::End::doPhase() {}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



StandardGamePhases::Finish::Finish(GameComponents &components) : AbstractGamePhase(GamePhase::GAME_FINISH, components) {}

StandardGamePhases::Finish::~Finish() {}

void StandardGamePhases::Finish::doPhase() {}