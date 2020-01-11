#pragma once
#include "EnumPriority.h"

class Event;

class Rule final {
public:
	const char* trigger;
	bool(*condition)(Event&);
	void(*payload)(Event&);
	Priority priority = Priority::INVALID;
	//Source source

	Rule(const char *trigger);
	Rule(const char *trigger, bool(*condition)(Event&), void(*effect)(Event&), Priority priority);
	~Rule();

	bool meetsRequirements(Event &e);
	void activate(Event &e);

private:
};

