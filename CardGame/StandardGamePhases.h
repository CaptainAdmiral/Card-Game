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

	class Planning : public AbstractGamePhase, IMouseListener {
	public:
		Planning(GameComponents&, Player*, PhaseCycle*);
		~Planning();

		Card *draggedCard = nullptr;
		int draggedReturnX = 0;
		int draggedReturnY = 0;

		void onPhaseStart() override;
		void onPhaseEnd() override;

		void doPhase() override;

		virtual void onMousePressed(int x, int y) override;
		virtual void onMouseReleased(int x, int y) override;

	private:
		Button<void(AbstractGamePhase::*)(), AbstractGamePhase> button;
	};

	class Resolution : public AbstractGamePhase {
	public:
		Resolution(GameComponents&);
		~Resolution();
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
