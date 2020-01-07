#pragma once

namespace EventID {
	static const unsigned int getUniqueID() {
		static unsigned int curID;
		return ++curID;
	}
};

