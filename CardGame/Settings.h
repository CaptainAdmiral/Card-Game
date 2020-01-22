#pragma once

namespace Settings {
	namespace Debug {
		static constexpr bool DEBUG = true;
	}

	namespace General {
		static constexpr unsigned int DEFAULT_HEIGHT = 800;
		static constexpr unsigned int DEFAULT_WIDTH = 1000;
	}

	namespace UI {
		static constexpr float handHeight = 0.2f * General::DEFAULT_HEIGHT;
		static constexpr float cardWidth = handHeight / 2;
	}
};