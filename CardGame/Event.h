#pragma once
#include "EventID.h"

class Event {
public:
	static const unsigned int TYPE;

	Event() {}
	~Event() {}

	virtual const unsigned int getType() {
		return TYPE;
	}
};

