#pragma once
#include "AbstractGamePhase.h"
#include "IMouseListener.h"
#include "Button.h"

class GamePhasePlanning : public AbstractGamePhase, IMouseListener {
public:
	GamePhasePlanning(GameComponents&, Player*, PhaseCycle*);
	~GamePhasePlanning();

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