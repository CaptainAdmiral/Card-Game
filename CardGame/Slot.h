#pragma once
#include "ICardContainer.h"
#include<vector>

class Slot : public ICardContainer, public IRenderable {
public:
	static constexpr GameObjectType TYPE = GameObjectType::SLOT;

	int row = 0;
	int col = 0;

	Slot();
	Slot(float x, float y);
	Slot(float x, float y, float width, float height);
	Slot(float x, float y, float width, float height, int row, int col);
	virtual ~Slot();

	CardPtr contents;

	//Assert slot is empty (use isEmpty() or hasSpace() to check)
	virtual void card_in(CardPtr) override;
	virtual CardPtr card_out() override;
	virtual CardPtr card_out(Card&) override;
	virtual bool hasSpace() override;
	virtual bool isEmpty() override;
	virtual bool contains(Card&) override;

	virtual AbstractRender& getRender() override;

	virtual GameObjectType getType() override;

	float getHeight();
	float getWidth();
	void setWidth(float w);
	void setHeight(float h);

	virtual GameObjectType type() override {
		return TYPE;
	}

	struct Properties {
	public:
		enum Type { VOID, PLAINS, SUMMON, BASE, MANA  };

		Type type = VOID;

		bool canSummon() {
			return type == SUMMON;
		}

		Player *getController();

		void setController(Player *player);

	private:
		Player *controller = nullptr;
	};

	Properties properties;

protected:
	float height = 0;
	float width = 0;

	virtual BoundingBox calculateBoundingBox() override;
};