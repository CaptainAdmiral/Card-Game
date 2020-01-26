#include "Field.h"
#include "Settings.h"
#include "RenderField.h"
#include "RenderManager.h"
#include <algorithm>

Field::Blueprint::Blueprint(std::initializer_list<std::string> bp) : templateString(bp) {
	std::reverse(templateString.begin(), templateString.end());
}

Slot::Properties::Type Field::Blueprint::getSlotType(size_t row, size_t col) {
	return charToType.at(templateString[row][col]);
}

Field::Blueprint &Field::Blueprint::defineChar(char ch, Slot::Properties::Type slotType) {
	charToType[ch] = slotType;
	return *this;
}

Field::Field() {
	Blueprint blueprint = Blueprint({
	   //012345678
		
		"VVVSBSVVV",	//10
		"VSPPSPPSV",	//9
		"MSPPPPPSM",	//8
		"SPPPPPPPS",	//7
		"PPPPPPPPP",	//6
		"PPPPMPPPP",	//5
		"PPPPPPPPP",	//4
		"SSPPPPPSS",	//3
		"MSPPPPPSM",	//2
		"VVPSSSPVV",	//1
		"VVVVBVVVV"		//0

		}).defineChar('V', Slot::Properties::VOID)
		.defineChar('S', Slot::Properties::SUMMON)
		.defineChar('B', Slot::Properties::BASE)
		.defineChar('P', Slot::Properties::PLAINS)
		.defineChar('M', Slot::Properties::MANA);

	buildField(blueprint);
}

Field::Field(const Field &field) {
	buildField(field);
}

Field &Field::operator=(const Field &field) {
	if(this != &field) {
		buildField(field);
	}
	return *this;
}

Field::~Field() {}

AbstractRender &Field::getRender() {
	static RenderField render;
	return render;
}

void Field::buildField() {
	for(size_t i = 0; i < std::size(slotArray); i++) {
		for(size_t j = 0; j < std::size(slotArray[i]); j++) {
			if(j%2 == 1 && i == 0) continue;
			int height = Settings::General::DEFAULT_HEIGHT;
			int width = Settings::General::DEFAULT_WIDTH;
			float hBuffer = Settings::UI::handHeight + height*0.01f;
			float wBuffer = width / 10.0f;
			slotArray[i][j] = std::make_unique<Slot>(
				wBuffer + j*((width - 2*wBuffer) / (std::size(slotArray[i])-1)),
				hBuffer + ((std::size(slotArray)-1 - i) + 0.5f*(j%2) - 1)*((height - 2*hBuffer) / (std::size(slotArray)-1)),
				1.25*(width - 2*wBuffer) / (std::size(slotArray[i])),
				(height - 2*hBuffer) / (std::size(slotArray)),
				i,
				j
			);
		}
	}
}

void Field::buildField(Blueprint blueprint) {
	buildField();
	for(size_t i = 0; i < std::size(slotArray); i++) {
		for(size_t j = 0; j < std::size(slotArray[i]); j++) {
			if(j%2 == 1 && i == 0) continue;
			slotArray[i][j]->properties.type = blueprint.getSlotType(i, j);
		}
	}
}

void Field::buildField(const Field &field) {
	for(size_t i = 0; i < std::size(slotArray); i++) {
		for(size_t j = 0; j < std::size(slotArray[i]); j++) {
			if(j%2 == 1 && i == 0) continue;
			slotArray[i][j] = std::make_unique<Slot>(
				field.slotArray[i][j]->getPosX(),
				field.slotArray[i][j]->getPosY(),
				field.slotArray[i][j]->getWidth(),
				field.slotArray[i][j]->getHeight(),
				field.slotArray[i][j]->row,
				field.slotArray[i][j]->col
			);

			slotArray[i][j]->properties = field.slotArray[i][j]->properties;

			if(field.slotArray[i][j]->contents == nullptr) continue;
			
			slotArray[i][j]->contents = std::make_unique<Card>(*(field.slotArray[i][j]->contents));
			slotArray[i][j]->contents->updateBoundingBox();
			slotArray[i][j]->contents->container = slotArray[i][j].get();
		}
	}
}

bool Field::slotMissing(unsigned int i, unsigned int j) {
	return j%2==1 && i==0;
}

void Field::displayAsAfterimage(bool flag) {
	for(size_t i = 0; i < std::size(slotArray); i++) {
		for(size_t j = 0; j < std::size(slotArray[i]); j++) {
			if(j%2 == 1 && i == 0) continue;
			slotArray[i][j]->setVisible(!flag);
			if(slotArray[i][j]->contents == nullptr) continue;
			slotArray[i][j]->contents->isAfterimage = flag;
			RenderManager::instance().bringToFront(slotArray[i][j]->contents.get());
		}
	}
}

void Field::bringCardsToFront() {
	for(size_t i = 0; i < std::size(slotArray); i++) {
		for(size_t j = 0; j < std::size(slotArray[i]); j++) {
			if(j%2 == 1 && i == 0) continue;
			if(slotArray[i][j]->contents == nullptr) continue;
			RenderManager::instance().bringToFront(slotArray[i][j]->contents.get());
		}
	}
}

void Field::for_each_slot(std::function<void(Slot&)> func) {
	for(size_t i = 0; i < std::size(slotArray); i++) {
		for(size_t j = 0; j < std::size(slotArray[i]); j++) {
			if(j % 2 == 1 && i == 0) continue;
			func(*slotArray[i][j]);
		}
	}
}

void Field::for_each_card(std::function<void(Card&)> func) {
	for(size_t i = 0; i < std::size(slotArray); i++) {
		for(size_t j = 0; j < std::size(slotArray[i]); j++) {
			if(j%2 == 1 && i == 0) continue;
			if(slotArray[i][j]->contents == nullptr) continue;
			func(*slotArray[i][j]->contents);
		}
	}
}
