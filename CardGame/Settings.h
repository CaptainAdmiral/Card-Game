#pragma once

namespace Settings {
	namespace Debug {
		static constexpr bool DEBUG = true;
	}

	namespace General {
		static constexpr unsigned int DEFAULT_HEIGHT = 600;
		static constexpr unsigned int DEFAULT_WIDTH = 400;
	}

	namespace UI {
		static constexpr float handHeight = 0.2f * General::DEFAULT_HEIGHT;
		static constexpr float cardWidth = handHeight / 2;
	}
};