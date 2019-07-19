#include "ICardContainer.h"

bool ICardContainer::giveCardTo(ICardContainer &container) {
	if(isEmpty() || !container.hasSpace()) return false;
	container.card_in(std::move(card_out()));
	return true;
}

bool ICardContainer::giveCardTo(ICardContainer &container, Card &card) {
	if(!contains(card) || !container.hasSpace()) return false;
	container.card_in(std::move(card_out(card)));
	return true;
}
