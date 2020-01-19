#include "Player.h"

Player::Player() {}
Player::~Player() {}

void Player::draw() {
	deck.giveCardTo(hand);
}

void Player::draw(int amount) {
	for (int i = 0; i < amount; i++) {
		draw();
	}
}

void Player::setVisible(bool vis) {
	hand.setVisible(vis);
	for(CardPtr& card : hand.contents) {
		card->setVisible(vis);
	}
}