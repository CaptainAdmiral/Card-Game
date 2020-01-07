#pragma once
#include "Event.h"

class IEventListener {
public:
	IEventListener() {}
	virtual ~IEventListener() {}

	virtual void notify(Event e) = 0;
};
