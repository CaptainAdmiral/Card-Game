#pragma once
#include "EnumPriority.h"
#include <functional>

class Event;

class Rule final {
public:
	const char* trigger;
	std::function<bool(Event&)> condition;
	std::function<void(Event&)> payload;
	Priority priority = Priority::INVALID;
	//Source source

	Rule(const char *trigger);
	Rule(const char *trigger, std::function<bool(Event&)>, std::function<void(Event&)>, Priority priority);
	~Rule();

	bool meetsRequirements(Event &e);
	void activate(Event &e);

private:
};

