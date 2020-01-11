#include "Field.h"
#include "Settings.h"
#include "RenderField.h"

Field::Field() {
	buildField();
}

Field::Field(const Field &field) {
	buildField(field);
}

Field & Field::operator=(const Field &field) {
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
			if(i%2 == 0 && j == 0) continue;
			int height = Settings::General::DEFAULT_HEIGHT;
			int width = Settings::General::DEFAULT_WIDTH;
			float hBuffer = Settings::UI::handHeight;
			float wBuffer = width / 15.0f;
			slotArray[i][j] = std::make_unique<Slot>(
				wBuffer + (j + 0.5f*(i%2))*((width - 2*wBuffer) / (std::size(slotArray[i]))),
				hBuffer + i*((height - 2*hBuffer) / (std::size(slotArray))),
				(width - 2*wBuffer) / (std::size(slotArray[i])) - 4,
				(height - 2*hBuffer) / (std::size(slotArray)) * 2 - 4,
				std::size(slotArray)-1-i,
				std::size(slotArray[i])-1-j
			);
		}
	}
}

void Field::buildField(const Field& field) {
	for(size_t i = 0; i < std::size(slotArray); i++) {
		for(size_t j = 0; j < std::size(slotArray[i]); j++) {
			if(i%2 == 0 && j == 0) continue;
			slotArray[i][j] = std::make_unique<Slot>(
				field.slotArray[i][j]->getPosX(),
				field.slotArray[i][j]->getPosY(),
				field.slotArray[i][j]->getWidth(),
				field.slotArray[i][j]->getHeight(),
				field.slotArray[i][j]->row,
				field.slotArray[i][j]->col
			);
			slotArray[i][j]->setVisible(false);
			if(field.slotArray[i][j]->contents == nullptr) continue;
			slotArray[i][j]->contents = std::make_unique<Card>(*(field.slotArray[i][j]->contents));
			slotArray[i][j]->contents->container = slotArray[i][j].get();
		}
	}
}

void Field::displayAsAfterimage(bool flag) {
	for(size_t i = 0; i < std::size(slotArray); i++) {
		for(size_t j = 0; j < std::size(slotArray[i]); j++) {
			if(i % 2 == 0 && j == 0) continue;
			if(slotArray[i][j]->contents == nullptr) continue;
			slotArray[i][j]->contents->isAfterimage = flag;
		}
	}
}
