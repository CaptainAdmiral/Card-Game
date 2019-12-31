#include "Field.h"

Field::Field() {
	buildField();
}

Field::~Field() {

}

AbstractRender &Field::getRender() {
	static RenderField render;
	return render;
}

void Field::buildField() {
	for(size_t i = 0; i < std::size(slotArray); i++) {
		for(size_t j = 0; j < std::size(slotArray[i]); j++) {
			if(i%2 == 0 && j == 0) continue;
			slotArray[i][j] = std::make_unique<Slot>((j + 0.5f*(i%2))*100, (i + 1)*100, 98);
		}
	}
}