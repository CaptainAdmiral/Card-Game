#pragma once
#include "Card.h"
#include <memory>
#include <assert.h>


typedef std::unique_ptr<Card> CardPtr;

class ICardContainer {
public:

	//Request to move unique pointer into card container
	//Assert container has space (use hasSpace() to check)
	virtual void card_in(CardPtr) = 0;

	//Removes and returns a single card from the contents of the card container
	//Up to the specific class to provide an implementation for which card is returned
	//Assert container is not empty (use isEmpty() to check)
	//Return unique pointer to removed card
	virtual CardPtr card_out() = 0;

	//Removes and returns a single specified card from the contents of the card container
	//Assert specified card is in the container (Use contains(Card&) to check)
	//Return unique pointer to removed card or nullptr if card is not in container
	virtual CardPtr card_out(Card&) = 0;

	//Returns whether or not the container has space for another card
	virtual bool hasSpace() = 0;

	//Returns whether or not the container is empty
	virtual bool isEmpty() = 0;

	//Returns whether or not the container contains the specified card
	virtual bool contains(Card&) = 0;

	//Moves a card out of the container this method is called from into the specified container.
	//Return true if anything was moved else false
	virtual bool giveCardTo(ICardContainer&);

	//Moves a specified card out of the container this method is called from into the specified container.
	//Return true if anything was moved else false
	virtual bool giveCardTo(ICardContainer&, Card&);
};