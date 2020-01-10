#include "AbstractCardContainer.h"
#include <algorithm>

void AbstractCardContainer::card_in(CardPtr card) {
	card->container = this;
	contents.push_back(std::move(card));
}

CardPtr AbstractCardContainer::card_out() {
	assert(!contents.empty());
	CardPtr lastElement = std::move(contents.back());
	contents.pop_back();
	lastElement->container = nullptr;
	return std::move(lastElement);
}

CardPtr AbstractCardContainer::card_out(Card &card) {
	CardCollection::iterator iterator = std::find_if(contents.begin(), contents.end(), [&](CardPtr &cardptr) {return cardptr.get() == &card; });
	assert(iterator != contents.end());
	card.container = nullptr;
	CardPtr temp = std::move(*iterator);
	contents.erase(iterator);
	return std::move(temp);
}

bool AbstractCardContainer::hasSpace() {
	return true;
}

bool AbstractCardContainer::isEmpty() {
	return contents.empty();
}

bool AbstractCardContainer::contains(Card &card) {
	return card.container == this;
}