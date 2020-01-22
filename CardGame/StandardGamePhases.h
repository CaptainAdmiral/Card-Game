#pragma once
#include "AbstractGamePhase.h"
#include "IMouseListener.h"
#include "Button.h"
#include "Action.h"
#include <vector>
#include <map>

class PhaseCycle;

namespace StandardGamePhases {
	class Start : public AbstractGamePhase {
	public:
		Start(GameComponents&, Player*, PhaseCycle*);
		~Start();
		void doPhase() override;
	};

	class Draw : public AbstractGamePhase {
	public:
		Draw(GameComponents&, Player*);
		~Draw();
		void doPhase() override;
	};

	class End : public AbstractGamePhase {
	public:
		End(GameComponents&);
		~End();
		void doPhase() override;
	};

	class Finish : public AbstractGamePhase {
	public:
		Finish(GameComponents&);
		~Finish();
		void doPhase() override;
	};
};
