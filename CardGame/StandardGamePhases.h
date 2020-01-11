#pragma once
#include "AbstractGamePhase.h"
#include "IMouseListener.h"
#include "Button.h"
#include <map>

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
		GamePhase_Planning(GameComponents&, PhaseCycle*);
		~GamePhase_Planning();

		std::unique_ptr<Field> field;

		Button<void(AbstractGamePhase::*)(), AbstractGamePhase> button;

		Card *draggedCard = nullptr;
		int draggedReturnX = 0;
		int draggedReturnY = 0;

		void onPhaseStart() override;

		void doPhase() override;

		virtual void onMousePressed(int x, int y);
		virtual void onMouseReleased(int x, int y);
	private:
		unsigned int summons;
		std::map<Card*, int> cardMoves;
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
