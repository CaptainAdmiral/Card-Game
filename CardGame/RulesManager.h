#pragma once
#include "rule.h"
#include "IEventListener.h"
#include <vector>

struct GameComponents;
class PhaseCycle;

class RulesManager : IEventListener {
public:
	RulesManager(GameComponents &components, PhaseCycle &cycle);
	RulesManager(const RulesManager&) = delete;
	RulesManager &operator = (const RulesManager&) = delete;
	RulesManager(RulesManager&&) = delete;
	RulesManager &operator = (RulesManager&&) = delete;

	~RulesManager();

	GameComponents &gameComponents;
	PhaseCycle &phaseCycle;

	std::vector<Rule> rules; //global passives

	virtual void notify(Event &e) override;

private:
	void addBaseRules();
};

