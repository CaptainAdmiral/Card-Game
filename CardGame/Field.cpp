#include "Field.h"
#include "Settings.h"
#include "RenderField.h"

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
			int height = Settings::General::DEFAULT_HEIGHT;
			int width = Settings::General::DEFAULT_WIDTH;
			int hBuffer = Settings::UI::handHeight;
			int wBuffer = width / 15;
			slotArray[i][j] = std::make_unique<Slot>(
				wBuffer + (j + 0.5f*(i%2))*((width - 2*wBuffer) / (std::size(slotArray[i]))),
				hBuffer + i*((height - 2*hBuffer) / (std::size(slotArray))),
				(width - 2*wBuffer) / (std::size(slotArray[i])) - 4,
				(height - 2*hBuffer) / (std::size(slotArray)) * 2 - 4
			);
		}
	}
}