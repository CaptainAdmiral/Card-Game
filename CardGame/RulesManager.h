#pragma once
#include "GameComponents.h"
#include "source.h"
#include "EnumPriority.h"
#include "Effect.h"
#include <vector>

class RulesManager {
public:
	RulesManager(GameComponents&);
	~RulesManager();

	

private:
	struct Rule {
		Source source;
		//Event trigger
		Effect effect;	//Code to execute on trigger //Built from card effect text
		Priority priority;
	};

	std::vector<Rule> rules; //global passives
};

