#pragma once

namespace Settings {
	namespace Debug {
		static const bool DEBUG = true;
	}

	namespace General {
		static const unsigned int DEFAULT_HEIGHT = 500;
		static const unsigned int DEFAULT_WIDTH = 300;
	}

	namespace UI {
		static float handHeight = 0.2f * General::DEFAULT_HEIGHT;
	}
};