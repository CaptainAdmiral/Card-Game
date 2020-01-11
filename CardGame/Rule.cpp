#include "Rule.h"

Rule::Rule(const char * trigger) : trigger(trigger) {}

Rule::Rule(const char *trigger, bool(*condition)(Event&), void(*effect)(Event&), Priority priority) : trigger(trigger), condition(condition), payload(effect), priority(priority) {}

Rule::~Rule() {}

bool Rule::meetsRequirements(Event &e) {
	return !condition? true : (*condition)(e);
}

void Rule::activate(Event &e) {
	(*payload)(e);
}
