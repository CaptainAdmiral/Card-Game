#pragma once
#include "IRenderable.h"
#include "Slot.h"
#include <map>
#include <String>
#include <initializer_list>
#include <vector>
#include <functional>

class Field : IRenderable {
public:
	Field();
	Field(const Field&); //WARNING - Copy constructor creates deep copy only
	Field &operator=(const Field&); //WARNING - Copy constructor creates deep copy only
	~Field();

	struct Blueprint {
		Blueprint(std::initializer_list<std::string> bp);
		Slot::Properties::Type getSlotType(size_t row, size_t col);
		Blueprint &defineChar(char ch, Slot::Properties::Type slotType);

	private:
		std::vector<std::string> templateString;
		std::map<char, Slot::Properties::Type> charToType;
	};

	std::unique_ptr<Slot> slotArray[11][9];
	
	AbstractRender &getRender() override;

	//Initialized an empty field of void slots
	void buildField();

	//Creates a field with slot types based on the supplied blueprint
	void buildField(Blueprint blueprint);

	//Deep copies the contents of the supplied field
	void buildField(const Field&);

	static bool slotMissing(unsigned int i, unsigned int j);

	//Causes the fields slots not to be rendered and the cards to be rendered semi-transparently
	void displayAsAfterimage(bool flag);

	//Brings all the cards on the field to the front of the render list;
	void bringCardsToFront();

	//Executes the function on each slot on the field;
	void for_each_slot(std::function<void(Slot&)> func);

	//Executes the function on each card on the field;
	void for_each_card(std::function<void(Card&)> func);
};