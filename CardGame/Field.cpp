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
			slotArray[i][j] = std::make_unique<Slot>();
		}
	}
}