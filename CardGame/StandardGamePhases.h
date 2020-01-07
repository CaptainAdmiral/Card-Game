#pragma once
#include "AbstractGamePhase.h"
#include "IMouseListener.h"

class PhaseCycle;

struct StandardGamePhases {
	class GamePhase_Start : public AbstractGamePhase {
	public:
		GamePhase_Start(GameComponents&, PhaseCycle*);
		~GamePhase_Start();
		void doPhase() override;
	};

	class GamePhase_Draw : public AbstractGamePhase {
	public:
		GamePhase_Draw(GameComponents&);
		~GamePhase_Draw();
		void doPhase() override;
	};

	class GamePhase_Planning : public AbstractGamePhase, IMouseListener {
	public:
		GamePhase_Planning(GameComponents&);
		~GamePhase_Planning();
		void doPhase() override;

		virtual void onMouseReleased(int x, int y);
		virtual void onMousePressed(int x, int y);
	};

	class GamePhase_Action : public AbstractGamePhase {
	public:
		GamePhase_Action(GameComponents&);
		~GamePhase_Action();
		void doPhase() override;
	};

	class GamePhase_End : public AbstractGamePhase {
	public:
		GamePhase_End(GameComponents&);
		~GamePhase_End();
		void doPhase() override;
	};

	class GamePhase_Finish : public AbstractGamePhase {
	public:
		GamePhase_Finish(GameComponents&);
		~GamePhase_Finish();
		void doPhase() override;
	};
};
