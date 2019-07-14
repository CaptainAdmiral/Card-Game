#pragma once
#include "AbstractGamePhase.h"
#include "GameComponents.h"

struct StandardGamePhases {
	class GamePhase_Draw : public AbstractGamePhase {
	public:
		GameComponents &gameComponents;
		GamePhase_Draw(GameComponents&);
		~GamePhase_Draw();
		void doPhase() override;
	};

	class GamePhase_Planning : public AbstractGamePhase {
	public:
		GameComponents &gameComponents;
		GamePhase_Planning(GameComponents&);
		~GamePhase_Planning();
		void doPhase() override;
	};

	class GamePhase_Action : public AbstractGamePhase {
	public:
		GameComponents &gameComponents;
		GamePhase_Action(GameComponents&);
		~GamePhase_Action();
		void doPhase() override;
	};

	class GamePhase_End : public AbstractGamePhase {
	public:
		GameComponents &gameComponents;
		GamePhase_End(GameComponents&);
		~GamePhase_End();
		void doPhase() override;
	};
};
