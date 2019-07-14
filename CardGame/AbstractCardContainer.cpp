#include "AbstractCardContainer.h"

void AbstractCardContainer::card_in(CardPtr card) {
	contents.push_back(std::move(card));
}

CardPtr AbstractCardContainer::card_out() {
	assert(!contents.empty());
	CardPtr lastElement = std::move(contents.back());
	contents.pop_back();
	return std::move(lastElement);
}

CardPtr AbstractCardContainer::card_out(Card &card) {
	CardCollection::iterator iterator = std::find_if(contents.begin(), contents.end(), [&](CardPtr &cardptr) {return cardptr.get() == &card; }); //TODO check for copy constructor violation
	assert(iterator != contents.end());
	return std::move(*iterator);
}

bool AbstractCardContainer::hasSpace() {
	return true;
}

bool AbstractCardContainer::isEmpty() {
	return contents.empty();
}

//TODO
bool AbstractCardContainer::contains(Card&) {
	return false;
}